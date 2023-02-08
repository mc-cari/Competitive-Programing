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
#define PI acos(-1.0) 
//#define double long long //Para usar enteros

//https://www.urionlinejudge.com.br/judge/es/problems/view/1137

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


db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }
double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double

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

bool areSame(line l1, line l2) {           // also check coefficient c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS); }

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;            // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
  else                  p.y = -(l2.a * p.x + l2.c);
  return true; }


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


// returns true if point d is inside the circumCircle defined by a,b,c
int inCircumCircle(point a, point b, point c, point d) {
  return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
         (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
         ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
         (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
         (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}


int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n;
  while(cin>>n)
  {
    if(n==0)break;
    vector<point>Q;
    point a;
    for(int i=0;i<n;i++)
    {
      cin>>a.x>>a.y;
      Q.push_back(a);
    }
    if(n<=2)
    {
      cout<<n<<"\n";
      continue;
    }
    ll maxi=0;
    for(int i=0;i<n;i++)
    {
      for(int j=i+1;j<n;j++)
      {
        for(int z=j+1;z<n;z++)
        {
          point ctr;
          db R;
          if(circumCircle(Q[i], Q[j], Q[z], ctr, R)){
            ll res = 0;
            R=dist_sq(Q[i],ctr);
            for(int k=0;k<n;k++)
            {
              if(k==i||k==j||k==z)continue;
              if(dist_sq(Q[k],ctr)==R)
                res++;
            }
            maxi=max(maxi,res+3);
          }
        }
      }
    }
    if(maxi==0)maxi=2;
    cout<<maxi<<"\n";
  }

}
