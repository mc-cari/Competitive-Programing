#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))
//https://codeforces.com/problemset/problem/630/O
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }
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
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } };

double dist(point p1, point p2) {                // Euclidean distance
                      // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double rad) {
  // multiply theta with PI / 180.0
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

point translate(point p, vec v) {        // translate p according to v
  return point(p.x+v.x, p.y+v.y); }

vec rotate(vec p, double rad) {

  return vec(p.x * cos(rad) - p.y*sin(rad),
               p.x * sin(rad) + p.y*cos(rad)); }
// convert point and gradient/slope to line, A PARTIR DE UNA DIRECCION M
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


bool SegmentIntersection(point a1, point a2, point b1, point b2, point& ans)
{
    line A,B;
    point I;
    pointsToLine(a1,a2,A);
    pointsToLine(a1,a2,A);
    if (areIntersect(A,B,I) && distToLineSegment(I, a1, a2, ans) == 0 && distToLineSegment(I, b1, b2, ans) == 0)
    {
        return 1;
    }
    return 0;
}

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa)*norm_sq(ob))); }

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


int32_t main()
{
    point p;
    vec V(0,0);
    double a,b,c,d;
    cin>>p.x>>p.y>>V.x>>V.y>>a>>b>>c>>d;
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, b);
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
    V = rotate(V,PI-atan(a*0.5/b));
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, sqrt(a*a/4.0+b*b));
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
    V = rotate(V,PI-(PI*0.5-atan(a*0.5/b)));
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, (a-c)*0.5);
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
    V = rotate(V,1.5*PI);
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, d);
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
    V = rotate(V,0.5*PI);
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, c);
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
    V = rotate(V,0.5*PI);
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, d);
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
    V = rotate(V,1.5*PI);
    V = scale(V, 1/sqrt(norm_sq(V)));
    V = scale(V, (a-c)*0.5);
    p = translate(p,V);
    cout<<fixed<<setprecision(12)<<p.x<<" "<<p.y<<endl;
}
