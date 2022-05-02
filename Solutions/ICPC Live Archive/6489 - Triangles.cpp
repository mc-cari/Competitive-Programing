#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4500

struct point { db x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(db _x, db _y) : x(_x), y(_y) {}
    bool operator < (point other) const { // override less than operator
    if (fabs(y-other.y) > EPS)                   // useful for sorting
      return y < other.y;          // first criteria , by x-coordinate
    return x < other.x; }          // second criteria, by y-coordinate
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
    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }
  };      // constructor

db dist(point& p1, point& p2) {                // Euclidean distance
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }

struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y); }

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > -EPS; }

// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; } 

bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }

double anglet(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  db ang = acos(dot(oa, ob) / sqrt(norm_sq(oa)*norm_sq(ob)));
  if(ang!=0&&!collinear(a,o,b)&&ccw(a,o,b))ang = 2*PI - ang;
  return ang; }  

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x*s, v.y*s); }                   // shorter.same.longer
point translate(point p, vec v) {        // translate p according to v
  return point(p.x+v.x, p.y+v.y); }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
  // formula: c = a + u*ab
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u));                  // translate a to c
  return dist(p, c); }           // Euclidean distance between p and c

int main()
{
  ll n;
  while(cin >> n && n)
  {
    db x, y;
    vector<point> Qe, Q, ord;
    vl in(n, 0);
    for(int i = 0; i < n; i++)
    {
      cin >> x >> y;
      point p(x, y);
      Q.push_back(p);

    }
    sort(ALL(Q));
    for(int i = 0; i < n; i++)
    {
      in[i] = i;
      ord.push_back(Q[i]);
    }
    
    vector<tuple<ll, ll, ll> > rec;
    for(int i = 0; i < n; i++)for(int j = i+1; j < n; j++)
    {
      rec.push_back(make_tuple((Q[j] - Q[i]).ang(), i, j));
    }
    
    sort(ALL(rec));
    db mini = INF, maxi = 0;
    for(int i = 0; i < rec.size(); i++)
    {
      db angg, a, b;
      point aux;
      tie(angg, a, b) = rec[i];
      maxi = max(maxi, dist(Q[a], Q[b]) * distToLine(ord[n-1], Q[a], Q[b], aux));

      ll ind = in[a];
      while(ind >= 0 && (ord[ind] == Q[a] || ord[ind] == Q[b]))ind--;
      if(ind >= 0) mini = min(mini, dist(Q[a], Q[b]) * distToLine(ord[ind], Q[a], Q[b], aux));
      swap(ord[in[a]], ord[in[b]]); swap(in[a], in[b]);
    }
    cout<<mini * 0.5<< " " << maxi * 0.5 << "\n";
  }
}
