#include "../Header.cpp"

double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }

//#define db long long    

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }
    point rot45(){ return point(x + y, y - x); }

    // by angles but with cross
    bool half() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const point &p) const
    {
        int h1 = half(), h2 = p.half();
        return h1 != h2 ? h1 > h2 : ((*this) ^ p) > 0;
    }

    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

};

db dist(const point& p1,const point& p2) {             
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }


point rotate(point p, db rad) {
  return point(p.x * cos(rad) - p.y*sin(rad),
               p.x * sin(rad) + p.y*cos(rad)); }


struct line { db a, b, c; };      


void pointsToLine(point p1, point p2, line &l) { 
  if (fabs(p1.x-p2.x) < EPS)                  // vertical line is fine
    l = {1.0, 0.0, -p1.x};                           // default values
  else {
    db a = -(db)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a,
         1.0,              // IMPORTANT: we fix the value of b to 1.0
         -(db)(a*p1.x) - p1.y}; }
  }

// for integers, normalized
void pointsToLine(point& p1, point p2, line &l) { 
  l.a = p1.y - p2.y;
  l.b = p2.x - p1.x;
  l.c = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
  ll g = __gcd(abs(l.a), __gcd(abs(l.b), abs(l.c)));
  ll sgn = 1;
  if(l.a < 0 || (l.a == 0 && l.b < 0))sgn = -1;
  l.a /= g * sgn; l.b /= g * sgn; l.c /= g * sgn;
}
// not needed since we will use the more robust form: ax + by + c = 0
struct line2 { db m, c; };      // another way to represent a line

int pointsToLine2(point p1, point p2, line2 &l) {
 if (abs(p1.x-p2.x) < EPS) {            // special case: vertical line
   l.m = INF;                    // l contains m = INF and c = x_value
   l.c = p1.x;                  // to denote vertical line x = x_value
   return 0;   // we need this return variable to differentiate result
 }
 else {
   l.m = (db)(p1.y-p2.y) / (p1.x-p2.x);
   l.c = p1.y - l.m*p1.x;
   return 1;     // l contains m and c of the line equation y = mx + c
} }

bool areParallel(line l1, line l2) {       // check coefficients a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) {           // also check coefficient c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS); }

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;            // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                  p.y = -(l2.a*p.x + l2.c);
  return true; }

// Or use pointsToSlope, Revisar, mejor con 2 puntos
void perpendicular_line(point a, line l, line& ans)
{
    point b((-l.b*a.y-l.c)/l.a,a.y+1);
    b.x-=a.x;
    b.y-=a.y;
    b = rotate(b,90);
    b.x+=a.x;
    b.y+=a.y;
    pointsToLine(a,b, ans);
}


//Scalar projection of vector a onto vector b
// if s < -EPS or s > |b| + EPS then the projection is not on the segment
db sproject(point a, point b)
{
  return a*b/sqrt(b.norm_sq());
}

bool onSegment(const point& p, const point& p1, const point& p2)
{
    bool x = (abs(p1.x - p2.x) < EPS && abs(p.x - p2.x) < EPS) || (p.x <= max(p1.x, p2.x) && p.x >= min(p1.x, p2.x));
    bool y = (abs(p1.y - p2.y) < EPS && abs(p.y - p2.y) < EPS) || (p.y <= max(p1.y, p2.y) && p.y >= min(p1.y, p2.y));
    return x && y;
}

// convert point and gradient/slope to line, A PARTIR DE UNA DIRECCION M
// usar 1/l.a para calcular perpendicular
void pointSlopeToLine(point p, db m, line &l) {
  l.a = -m;                                               // always -m
  l.b = 1;                                                 // always 1
  l.c = -((l.a*p.x) + (l.b*p.y)); }                    // compute this

void closestPoint(line l, point p, point &ans) {
  line perpendicular;         // perpendicular to l and pass through p
  if (fabs(l.b) < EPS) {              // special case 1: vertical line
    ans.x = -(l.c);   ans.y = p.y;      return; }

  if (fabs(l.a) < EPS) {            // special case 2: horizontal line
    ans.x = p.x;      ans.y = -(l.c);   return; }

  pointSlopeToLine(p, 1/l.a, perpendicular);            // normal line
  // intersect line l with this perpendicular line
  // the intersection point is the closest point
  areIntersect(l, perpendicular, ans); }

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point &ans) {
  point b;
  closestPoint(l, p, b);                     // similar to distToLine
  point v = (b - p);                             // create a vector
  ans = p + v + v; }         // translate p twice

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
db distToLine(point p, point a, point b, point &c) {
  // formula: c = a + u*ab
  point ap = (p - a), ab = (b - a);
  db u = ap * ab / ab.norm_sq();
  c = a + ab * u;                  // translate a to c
  return dist(p, c); }           // Euclidean distance between p and c

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
db distToLineSegment(point p, point a, point b, point &c) {
  point ap = (p - a), ab = (b - a);
  db u = ap * ab / ab.norm_sq();
  if (u < 0.0) { c = point(a.x, a.y);                   // closer to a
    return dist(p, a); }         // Euclidean distance between p and a
  if (u > 1.0) { c = point(b.x, b.y);                   // closer to b
    return dist(p, b); }         // Euclidean distance between p and b
  return distToLine(p, a, b, c); }          // run distToLine as above

bool ccw(point p, point q, point r) {
  return ((q - p)^(r - p)) > -EPS; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(((q - p)^(r - p))) < EPS; }


// angle from 0 to 2*PI
db anglet(point a, point o, point b) {  // returns angle aob in rad
  point oa = (a - o), ob = (b - o);
  db ang = acos(oa * ob / sqrt(oa.norm_sq()*ob.norm_sq()));
  if(ang!=0&&!collinear(a,o,b)&&ccw(a,o,b))ang = 2*PI - ang;
  return ang; }  // better

db angle(point a, point o, point b) {  // returns angle aob in rad
  point oa = (a - o), ob = (b - o);
  return acos(oa * ob / sqrt(oa.norm_sq()*ob.norm_sq())); }

point min(point a,point b)
{
    if(a<b)return a;
    return b;
}
point max(point a, point b)
{
    if(!(a<b))return a;
    return b;
}

// 0 -> No intersection, 1 -> Point intersection, 2 -> segment intersection
int SegmentIntersection(point a1, point a2, point b1, point b2, point& ans, point& ans2)
{
    line A,B;
    point I;
    pointsToLine(a1,a2,A);
    pointsToLine(b1,b2,B);
    if(areSame(A,B)&&!(a1==a2)&&!(b1==b2))
    {
        ans=max(min(a1,a2),min(b1,b2));
        ans2=min(max(a1,a2),max(b1,b2));
        if(ans2<ans)return 0;
        else if(ans == ans2)return 1;
        return 2;
    }
    if (a1==a2&&b1==b2)
    {
        if(a1==b1)
        {
            ans=a1;
            return 1;
        }
        return 0;
    }
    if(a1==a2)
    {
        if(fabs(distToLineSegment(a1, b1, b2, ans)-0.0) < EPS)
        {
            ans=a1;
            return 1;
        }
        return 0;
    }
    if(b1==b2)
    {
        if(fabs(distToLineSegment(b1, a1, a2, ans)-0.0) < EPS)
        {
            ans=b1;
            return 1;
        }
        return 0;
    }
    if (areIntersect(A,B,I) && fabs(distToLineSegment(I, a1, a2, ans)-0.0) < EPS && fabs(distToLineSegment(I, b1, b2, ans)-0 < EPS))
    {
        return 1;
    }
    return 0;
}


int32_t main() {
  vec a(1,3);
  cout<<30*PI/180<<endl;
  a = rotate(a, 30*PI/180);
  cout<<a.x<<" "<<a.y<<endl;

  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
