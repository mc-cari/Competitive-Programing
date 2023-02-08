#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))
 
 //https://www.urionlinejudge.com.br/judge/es/problems/view/2348
 
db DEG_to_RAD(db d) { return d * PI / 180.0; }

db RAD_to_DEG(db r) { return r * 180.0 / PI; }

struct point_i { int x, y;     // whenever possible, work with point_i
  point_i() { x = y = 0; }                      // default constructor
  point_i(int _x, int _y) : x(_x), y(_y) {} };          // constructor

struct point { db x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(db _x, db _y) : x(_x), y(_y) {}
    bool operator < (point other) const { // override less than operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;          // first criteria , by x-coordinate
    return y < other.y; }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator == (point other) const {
      return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
    point operator - (point other) const{
        point aux(x-other.x,y-other.y);
        return aux;
    }
    point operator + (point other) const{
        point aux(x+other.x,y+other.y);
        return aux;
    }
    point operator * (db other) const{
        point aux(x*other,y*other);
        return aux;
    }
  };      // constructor
int insideCircle(point_i p, point_i c, int r) { // all integer version
  int dx = p.x - c.x, dy = p.y - c.y;
  int Euc = dx * dx + dy * dy, rSq = r * r;             // all integer
  return Euc < rSq ? 0 : Euc == rSq ? 1 : 2; } //inside/border/outside

// P1 an d P2 intersections of circles and radius r -> pos of centers of circles of intersection
bool circle2PtsRad(point p1, point p2, db r, point &c) {
  db d2 = (p1.x - p2.x) * (p1.x - p2.x) +
              (p1.y - p2.y) * (p1.y - p2.y);
  db det = r * r / d2 - 0.25;
  if (det < 0.0) return false;
  db h = sqrt(det);
  c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
  c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
  return true; }         // to get the other center, reverse p1 and p2

  db dist(point p1, point p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y); }

// a = max x, b = max y from the center, AREA
db A_elipse(db a,db b)
{
    return a*b*PI;
}

// Length of segment with two points on the circunference
// separated by an angle
db chord(db r, db angle)
{
  return sqrt(2*r*r*(1-cos(angle)));
}

//Triangles
db perimeter(db ab, db bc, db ca) {
  return ab + bc + ca; }

db perimeter(point a, point b, point c) {
  return dist(a, b) + dist(b, c) + dist(c, a); }

db area(db ab, db bc, db ca) {
  // Heron's formula, split sqrt(a * b) into sqrt(a) * sqrt(b); in implementation
  db s = 0.5 * perimeter(ab, bc, ca);
  return sqrt(s) * sqrt(s - ab) * sqrt(s - bc) * sqrt(s - ca); }

db area(point a, point b, point c) {
  return area(dist(a, b), dist(b, c), dist(c, a)); }


// Area of the circle enclosed by an arc and a chord defined by an angle
db segment(db r, db angle)
{
  return  angle/2.0*r*r-area(chord(r,angle),r,r);
}

// And overlaping rectangle
bool rectangles_intersect(point a1,point a2,point b1,point b2,point& ans1, point& ans2)
{
  if(b1<a1)
  {
    swap(a1,b1);
    swap(a2,b2);
  }
  if(b1.x>=a2.x||b1.y>=a2.y||b2.y<=a1.y)return 0;
  ans1.x=b1.x;
  ans1.y=max(b1.y,a1.y);
  ans2.x=min(b2.x,a2.x);
  ans2.y=min(b2.y,a2.y);
  return 1;

}



//  from LINES ---
struct line { db a, b, c; }; // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
  if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
    l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
  } else {
    l.a = -(db)(p1.y - p2.y) / (p1.x - p2.x);
    l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
    l.c = -(db)(l.a * p1.x) - p1.y;
} }

bool areParallel(line l1, line l2) {        // check coefficient a + b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;            // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
  else                  p.y = -(l2.a * p.x + l2.c);
  return true; }

struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y); }

vec scale(vec v, db s) {        // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x * s, v.y * s); }               // shorter.same.longer

point translate(point p, vec v) {        // translate p according to v
  return point(p.x + v.x , p.y + v.y); }
// __________________

db rInCircle(db ab, db bc, db ca) {
  return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

db rInCircle(point a, point b, point c) {
  return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

// assumption: the required points/lines functions have been written
// returns 1 if there is an inCircle center, returns 0 otherwise
// if this function returns 1, ctr will be the inCircle center
// and r is the same as rInCircle
int inCircle(point p1, point p2, point p3, point &ctr, db &r) {
  r = rInCircle(p1, p2, p3);
  if (fabs(r) < EPS) return 0;                   // no inCircle center

  line l1, l2;                    // compute these two angle bisectors
  db ratio = dist(p1, p2) / dist(p1, p3);
  point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
  pointsToLine(p1, p, l1);

  ratio = dist(p2, p1) / dist(p2, p3);
  p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
  pointsToLine(p2, p, l2);

  areIntersect(l1, l2, ctr);           // get their intersection point
  return 1; }

db rCircumCircle(db ab, db bc, db ca) {
  return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

db rCircumCircle(point a, point b, point c) {
  return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

// assumption: the required points/lines functions have been written
// returns 1 if there is a circumCenter center, returns 0 otherwise
// if this function returns 1, ctr will be the circumCircle center
// and r is the same as rCircumCircle
int circumCircle(point p1, point p2, point p3, point &ctr, db &r){
  db a = p2.x - p1.x, b = p2.y - p1.y;
  db c = p3.x - p1.x, d = p3.y - p1.y;
  db e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
  db f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
  db g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
  if (fabs(g) < EPS) return 0;

  ctr.x = (d*e - b*f) / g;
  ctr.y = (a*f - c*e) / g;
  r = dist(p1, ctr);  // r = distance from center to 1 of the 3 points
  return 1; }

// https://www.nayuki.io/res/smallest-enclosing-circle/computational-geometry-lecture-6.pdf
// O(N) expected time

void smallest_enclosing_circle(vector<point>& pts, point& center, db& r) {
    random_shuffle(pts.begin(), pts.end());
    center = pts[0]; r = 0;
    int N = pts.size();
    for(int i=1;i<N;i++) {
        if (dist(pts[i] , center) > r + EPS) {
            center = pts[i];
            r = 0;
            for(int j=0;j<i;j++) {
                if (dist(pts[j] , center) > r + EPS) {
                    center = (pts[i] + pts[j]) * 0.5;
                    r = dist(pts[i] , center);
                    for(int k=0;k<j;k++) {
                        if (dist(pts[k] , center) > r + EPS) {
                            db rr;
                            circumCircle(pts[i], pts[j], pts[k],center,rr);
                            r = dist(pts[k] , center);
                        }
                    }
                }
            }
        }
    }
}

// returns true if point d is inside the circumCircle defined by a,b,c
int inCircumCircle(point a, point b, point c, point d) {
  return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
         (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
         (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
         (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}

bool canFormTriangle(db a, db b, db c) {
  return (a + b > c) && (a + c > b) && (b + c > a); }

int main()
{
  int n;
  db x;
  cin>>n;
  vector<db>c;
  deque<db>d;
  for(int i=0;i<n;i++)
  {
    cin>>x;
    c.push_back(x);
  }
  sort(ALL(c));
  for(int i=0;i<n;i++)
  {
    if(i%2==0)
    {
      d.push_back(c[i]);
    }
    else
    {
      d.push_front(c[i]);
    }
    
  }
  d.push_back(d[0]);
  db sum=0, angle=2*PI/n;
  for(int i=0;i<n;i++)
  {
    
    db l = sqrt(d[i]*d[i] + d[i+1]*d[i+1]- 2*d[i]*d[i+1]*cos(angle) );
    sum+=area(d[i],d[i+1],l);
  }
  cout<<fixed<<setprecision(3)<<sum<<"\n";
}
