#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }

//https://www.urionlinejudge.com.br/judge/es/problems/view/2907

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


// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }


int32_t main() {
  
    ll n;
    cin >> n;
    vector<point>Q;
    point a;

    for(int i = 0; i < n; i++)
    {
        cin >> a.x >> a.y;
        Q.push_back(a);
    }
    ll p2 = 1;
    ll sum = 0;
    for(int i = 0; i < n; i++)
    {
        vec v = toVec(Q[i], Q[(i+1)%n]);
        point c = translate(Q[p2%n], v);
        while(cross(toVec(Q[p2%n], c), toVec(Q[p2%n], Q[(p2+1)%n])) >= 0)
        {
            p2++;
            c = translate(Q[p2%n], v);
        }
        if(p2%n == i)continue;
        ll cant = p2 - i;
        cant--;
        
        sum += (cant*(cant-1))/2;
    }
    ll ans = (n*(n-1)*(n-2))/6 - sum;
    cout<<ans <<"\n";

  return 0;
}
