#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }

//https://codeforces.com/gym/102343/problem/H

// struct point_i { int x, y; };    // basic raw form, minimalist mode
struct point_i { int x, y;     // whenever possible, work with point_i
  point_i() { x = y = 0; }                      // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {} };         // user-defined

struct point { double x, y;   // only used if more precision is needed
  point() { x = y = 0.0; }                      // default constructor
  point(double _x, double _y) {
    x=_x;y=_y;
  }        // user-defined
  bool operator < (point other) const { // override less than operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;          // first criteria , by x-coordinate
    return y < other.y; }          // second criteria, by y-coordinate
    point operator - (point other) const{
        point aux(x-other.x,y-other.y);
        return aux;
    }
  // use EPS (1e-9) when testing equality of two floating points
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
  point operator + (point other) const{
      point aux(x+other.x,y+other.y);
      return aux;
  }
  point operator * (db other) const{
      point aux(x*other,y*other);
      return aux;
  }
   };
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
db dist(point& p1, point& p2) {                // Euclidean distance
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }


// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double rad) {
  return point(p.x * cos(rad) - p.y*sin(rad),
               p.x * sin(rad) + p.y*cos(rad)); }

// a*x + b*y + c = 0
struct line { double a, b, c; };          // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) { //RECTA
  if (fabs(p1.x-p2.x) < EPS)                  // vertical line is fine
    l = {1.0, 0.0, -p1.x};                           // default values
  else {
    double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a,
         1.0,              // IMPORTANT: we fix the value of b to 1.0
         -(double)(a*p1.x) - p1.y}; }
  }
// not needed since we will use the more robust form: ax + by + c = 0
struct line2 { double m, c; };      // another way to represent a line

int pointsToLine2(point p1, point p2, line2 &l) {
 if (abs(p1.x-p2.x) < EPS) {            // special case: vertical line
   l.m = INF;                    // l contains m = INF and c = x_value
   l.c = p1.x;                  // to denote vertical line x = x_value
   return 0;   // we need this return variable to differentiate result
 }
 else {
   l.m = (double)(p1.y-p2.y) / (p1.x-p2.x);
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
    pointsToLine(a,b,ans);
}


struct vec { double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x*s, v.y*s); }                   // shorter.same.longer

vec rotate(vec p, double theta) {
  double rad = (theta)*(PI / 180.0);    // multiply theta with PI / 180.0
  return vec(p.x * cos(rad) - p.y*sin(rad),
               p.x * sin(rad) + p.y*cos(rad)); }
point translate(point p, vec v) {        // translate p according to v
  return point(p.x+v.x, p.y+v.y); }

// convert point and gradient/slope to line, A PARTIR DE UNA DIRECCION M
// usar 1/l.a para calcular perpendicular
void pointSlopeToLine(point p, double m, line &l) {
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
  vec v = toVec(p, b);                             // create a vector
  ans = translate(translate(p, v), v); }         // translate p twice

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }// PRODUCTO PUNTO

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; } // CUADRADO DE LA NORMA

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
  // formula: c = a + u*ab
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u));                  // translate a to c
  return dist(p, c); }           // Euclidean distance between p and c

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) { c = point(a.x, a.y);                   // closer to a
    return dist(p, a); }         // Euclidean distance between p and a
  if (u > 1.0) { c = point(b.x, b.y);                   // closer to b
    return dist(p, b); }         // Euclidean distance between p and b
  return distToLine(p, a, b, c); }          // run distToLine as above

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

//// another variant
// returns 'twice' the area of this triangle A-B-c
// int area2(point p, point q, point r) {
//   return p.x * q.y - p.y * q.x +
//          q.x * r.y - q.y * r.x +
//          r.x * p.y - r.y * p.x;
// }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq

bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > -EPS; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }


// angle from 0 to 2*PI
double anglet(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  db ang = acos(dot(oa, ob) / sqrt(norm_sq(oa)*norm_sq(ob)));
  if(ang!=0&&!collinear(a,o,b)&&ccw(a,o,b))ang = 2*PI - ang;
  return ang; }  // better

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }


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

vector<point> Q;
vector<db>sums;
db W;
db value(db w, db i, db n)
{
  ll l=i,r=n-1,p;
  db ans = 0.0, acum = 0.0;
  while(l<=r)
  {
      p=(l+r)/2;
      ll sum = Q[p].x - Q[i].x;
      if(sum <= w)
      {
          l = p + 1;
          ans = p;
      }
      else r = p-1;
  }
  acum += sums[ans] - sums[i];
  if(ans < n-1)
  {
      line l1, l2;
      pointsToLine(Q[ans], Q[ans + 1], l1);
      point a1(Q[i].x + w, 0), a2(Q[i].x + w, 1);
      pointsToLine(a1, a2, l2);
      point result;
      if(!areIntersect(l1, l2, result))return 1;
      acum += (abs(Q[ans].y - result.y) / 2.0 + min(Q[ans].y, result.y) ) * (result.x - Q[ans].x);
  }
  l=0;r=i;
  ans = 0.0;
  while(l<=r)
  {
      p=(l+r)/2;
      ll sum = Q[i].x - Q[p].x;
      if(sum <= W - w)
      {
          r = p - 1;
          ans = p;
      }
      else l = p+1;
  }
  acum += sums[i] - sums[ans];
  if(ans > 0)
  {
      line l1, l2;
      pointsToLine(Q[ans], Q[ans - 1], l1);
      point a1(Q[i].x - (W - w), 0), a2(Q[i].x - (W - w), 1);
      pointsToLine(a1, a2, l2);
      point result;
      if(!areIntersect(l1, l2, result))return 1;
      acum += (abs(Q[ans].y - result.y) / 2.0 + min(Q[ans].y, result.y) ) * abs(result.x - Q[ans].x);
  }
  return acum;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    db maxx = 0;
    int n;
    cin >> n >> W;
    point a;
    
    sums.assign(n + 1, 0.0);
    for(int i = 0; i < n; i++)
    {
        cin >> a.x >> a.y;
        maxx = max(maxx, db(a.x));
        Q.push_back(a);
    }
    for(int i = 1; i < n; i++)
    {
        sums[i] = sums[i-1] + (abs(Q[i].y - Q[i-1].y) / 2.0 + min(Q[i-1].y, Q[i].y) )* (Q[i].x - Q[i-1].x);
    }
    db maxi = 0.0;
    for(int i = 0; i < n; i++)
    {
    
      db l=0,r=W;
      for(int j=0;j<=60;j++)
      {
          db d=(r-l)/3.0,m1=l+d,m2=r-d;
          db c1 = value(m1, i , n), c2 = value(m2, i ,n);
          if (c1 < c2) l = m1;
          else  r = m2;
          maxi = max(maxi, c1);
          maxi = max(maxi, c2);
      }
    }
    cout << fixed << setprecision(9) << maxi / W << "\n";
    
    return 0;
}
