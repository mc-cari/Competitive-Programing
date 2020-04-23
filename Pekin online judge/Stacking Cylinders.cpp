#include<vector>
#include<math.h>
#include<algorithm>
#include<iomanip>
#include<iostream>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;

//#define double long long Para usar enteros
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))
 
 //https://vjudge.net/problem/POJ-2194
 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
 
double RAD_to_DEG(double r) { return r*180.0 / PI; }
 
struct point { double x, y;   // only used if more precision is needed
    point() { x = y = 0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator == (point other) const {
        return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
    bool operator <(const point &p) const {
        return x < p.x || (fabs(x-p.x) < EPS && y < p.y); } 
    point operator + (point other) const{
      point aux(x+other.x,y+other.y);
      return aux;
  }
  };
 
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
double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double
 
// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {
  double result = 0.0;
  for (int i = 0; i < (int)P.size()-1; i++)  // remember that P[0] = P[n-1]
    result += dist(P[i], P[i+1]);
  return result; }
 
// returns the area
double area(const vector<point> &P) {
  int result = 0;
  for (int i = 0; i < (int)P.size()-1; i++)             // Shoelace formula
    result += (P[i].x*P[i+1].y - P[i+1].x*P[i].y); // if all points are int
  return fabs(result)/2; }     // result can be int(eger) until last step
 
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }
 
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }
 
double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }
 
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }
 
double area_alternative(const vector<point> &P) {
  double result = 0.0; point O(0.0, 0.0);
  for (int i = 0; i < (int)P.size()-1; i++)
    result += cross(toVec(O, P[i]), toVec(O, P[i+1]));
  return fabs(result) / 2.0; }
 
// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0; }
 
// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }
 
// returns true if we always make the same turn while examining
// all the edges of the polygon one by one
bool isConvex(const vector<point> &P) {
  int sz = (int)P.size();
  if (sz <= 3) return false;   // a point/sz=2 or a line/sz=3 is not convex
  bool firstTurn = ccw(P[0], P[1], P[2]);            // remember one result
  for (int i = 1; i < sz-1; i++)            // then compare with the others
    if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != firstTurn)
      return false;            // different sign -> this polygon is concave
  return true; }                                  // this polygon is convex
 
// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
  if ((int)P.size() < 3) return false;               // avoid point or line
  double sum = 0;    // assume the first vertex is equal to the last vertex
  for (int i = 0; i < (int)P.size()-1; i++) {
    if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
    else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
  return fabs(sum) > PI; }   // 360d -> in, 0d -> out, we have large margin
 
// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }
 
// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
// to cut the other side, swap (a,b)
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++) {
    double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
    if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
    if (left1 > -EPS) P.push_back(Q[i]);       // Q[i] is on the left of ab
    if (left1 * left2 < -EPS)        // edge (Q[i], Q[i+1]) crosses line ab
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());        // make P's first point = P's last point
  return P; }
 
vector<point> CH_Andrew(vector<point> &Pts) {
  int n = Pts.size(), k = 0;
  vector<point> H(2*n);
  sort(Pts.begin(), Pts.end());        // sort the points lexicographically
  for (int i = 0; i < n; i++) {                         // build lower hull
    while (k >= 2 && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  for (int i = n-2, t = k+1; i >= 0; i--) {             // build upper hull
    while (k >= t && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}
 
point pivot(0, 0);

point center_of_mass(vector <point>& Q)
{
    point ctr(0,0);
    for (int i=0;i<Q.size()-1;i++)
    {
        ctr = ctr + Q[i];
    }
    ctr.x/=Q.size()-1;
    ctr.y/=Q.size()-1;
    return ctr;
}
 
// Pick's theorem
// A = i + b/2 -1
// A: Area poligon with integer coords
// i: Interior points, b: points in the segments 
 
// with vector form of segment
// (x0,y0) + t(dx,dy)


point new_ctr(point a, point b)
{
  point mid((a.x+b.x)/2.0, (a.y + b.y)/2.0);
  vec tr = toVec(a,b);
  tr = scale(tr, 1/sqrt(norm_sq(tr)));
  double ydist = sqrt(4.0 - (dist(a,b)/2.0*dist(a,b)/2.0));
  tr = scale(tr, ydist);
  tr = rotate(tr, 90);
  mid = translate(mid, tr);
  return mid;
}
 
int main() {
  point a;
  int n;
  
  while (cin>>n)
  {
    vector<point>Q,P;
    if(n == 0) break;
    a.y = 1.0;
    for(int i=0; i < n; i++)
    {
      cin>>a.x;
      Q.push_back(a);
    }
    sort(ALL(Q));
    while(Q.size()!=1)
    {
      P.clear();
      for(int i = 0; i < Q.size() - 1; i++)
      {
        P.push_back(new_ctr(Q[i],Q[i+1]));
      }
      Q.clear();
      Q.assign(ALL(P));
    }
    cout<<fixed<<setprecision(4)<<Q[0].x<<" "<<Q[0].y<<"\n";
  }
  return 0;
}
