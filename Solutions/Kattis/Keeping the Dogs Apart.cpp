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

//https://open.kattis.com/problems/dogs

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


bool areParallel(line l1, line l2) {       // check coefficients a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) {           // also check coefficient c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS); }



struct vec { double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }


// returns the dot product of two vectors a and b
double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }// PRODUCTO PUNTO

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; } // CUADRADO DE LA NORMA


double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }


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



int main() {

    int n, m;
    vector<point>S, L;
    vector<db>angleS, angleL;
    point a;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
      cin>>a.x>>a.y;
      S.push_back(a);
      if (i != 0)
      {
        point aux(S[i-1].x + 1, S[i-1].y);
        angleS.push_back(anglet(aux, S[i-1], S[i]));
      }
    }
    cin >> m;
    for(int i = 0; i < m; i++)
    {
      cin >> a.x >> a.y;
      L.push_back(a);
      if (i != 0)
      {
        point aux(L[i-1].x + 1, L[i-1].y);
        angleL.push_back(anglet(aux, L[i-1], L[i]));
      }
    }
    ll inS = 0, inL = 0;
    db distS = 0, distL = 0, ans = dist(S[0], L[0]);
    point prevS = S[0], prevL = L[0];

    while(inS < n-1 && inL < m-1)
    {
      if(dist_sq(prevS, S[inS + 1]) <= dist_sq(prevL, L[inL + 1]))
      {
        db l=0,r=dist(prevS, S[inS + 1]),mini=1e12;
        for(int i=0;i<=100;i++)
        {
          double d=(r-l)/3.0,m1=l+d,m2=r-d;
          
          point auxS1(prevS.x + cos(angleS[inS])* m1, prevS.y + sin(angleS[inS]) * m1);
          point auxS2(prevS.x + cos(angleS[inS])* m2, prevS.y + sin(angleS[inS]) * m2);
          point auxL1(prevL.x + cos(angleL[inL])* m1, prevL.y + sin(angleL[inL]) * m1);
          point auxL2(prevL.x + cos(angleL[inL])* m2, prevL.y + sin(angleL[inL]) * m2);
          double c1 = dist(auxS1, auxL1), c2 = dist(auxS2, auxL2);
          if (c1 < c2) r = m2;
          else  l = m1;
          mini = min(mini, (c1+c2)/2.0);
        }
        ans = min(mini, ans);
        prevL.x += cos(angleL[inL]) * dist(prevS, S[inS + 1]);
        prevL.y += sin(angleL[inL]) * dist(prevS, S[inS + 1]);
        distS += dist(prevS, S[inS + 1]);
        distL += dist(prevS, S[inS + 1]);
        prevS = S[inS + 1];
        inS++;
      }
      else
      {
        db l=0,r=dist(prevL, L[inL + 1]),mini=1e12;
        for(int i=0;i<=100;i++)
        {
          double d=(r-l)/3.0,m1=l+d,m2=r-d;
          
          point auxS1(prevS.x + cos(angleS[inS])* m1, prevS.y + sin(angleS[inS]) * m1);
          point auxS2(prevS.x + cos(angleS[inS])* m2, prevS.y + sin(angleS[inS]) * m2);
          point auxL1(prevL.x + cos(angleL[inL])* m1, prevL.y + sin(angleL[inL]) * m1);
          point auxL2(prevL.x + cos(angleL[inL])* m2, prevL.y + sin(angleL[inL]) * m2);
          double c1 = dist(auxS1, auxL1), c2 = dist(auxS2, auxL2);
          if (c1 < c2) r = m2;
          else  l = m1;
          mini = min(mini, (c1+c2)/2.0);
        }
        ans = min(mini, ans);
        prevS.x += cos(angleS[inS]) * dist(prevL, L[inL + 1]);
        prevS.y += sin(angleS[inS]) * dist(prevL, L[inL + 1]);
        distS += dist(prevL, L[inL + 1]);
        distL += dist(prevL, L[inL + 1]);
        prevL = L[inL + 1];
        inL++;
      }
      
    }
    cout << setprecision(5) << fixed << ans << "\n";
  return 0;
}
