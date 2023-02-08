#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

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

db v, w, R;
point a2;

db angg(db a)
{
    if (a < 0) return a + 2. * PI;
    if (a >= 2. * PI) return a - 2. * PI;
    return a;
}

db value(db ang)
{

  db r_ang = ang + PI / 2.0;
  
  point r(cos(r_ang) * R, sin(r_ang) * R);
  if(dist(a2, r) < R)
  {
    return INF;
  }
  point aux(a2.x - r.x, a2.y - r.y);
  db d = dist(a2, r);
  db tan = sin(acos(R / d)) * d;

  db ang2 = acos(R / d);
  db ans = angg((a2 - r).ang() - ang2 + PI/2.0 - ang);


  if(ang > PI) ang = 2*PI - ang;
  return ang / w + ans / w + tan / v;
}

int main()
{
  db x, y;
  cin >> x >> y >> v >> w;
  y = abs(y);
  a2.x = x; a2.y = y;
  R = v / w;

  double l= a2.ang() - PI/2.0,r= a2.ang();
  a2.y = abs(a2.y);

  for(int i=0;i<=1000;i++)
  {
      double d=(r-l)/3.0,m1=l+d,m2=r-d;
      double c1 = value(angg(m1)), c2 = value(angg(m2));
      if (c2 < c1) l = m1;
      else if(c1 < c2) r = m2;
      else l = m1;
      
  }
  cout << fixed << setprecision(12) << value(angg((l + r) / 2.0)) << "\n";
}

// bug, cambio sentido rotación instantaneo
// al final solo se elige 1 sentido de giro final
/*
db value(db ang)
{
  db R = v / w;
  db r_ang = ang;
  if (ang >= 0)
  {
    r_ang += PI / 2.0;
  }
  else
  {
    r_ang -= PI / 2.0;
  }
  
  point r(cos(r_ang) * R, sin(r_ang) * R);
  point a1(0, 0);
  if(dist(a2, r) < R)
  {
    return INT_MAX;
  }
  db tan = sqrt(dist_sq(a2, r) - R * R);

  db ang2 = acos(R / dist(a2, r));
  
  db ans = anglet(a1, r, a2);
  if(ang >= 0)
  {
    ans -= ang2;
  }
  else
  {
    ans += ang2;
  }
  while(ans < -EPS) ans += 2*PI;
  while (ans > 2*PI - EPS) ans -= 2*PI;
  //cout<<fixed << setprecision(5)<<ang<<" "<<ans<<" "<<tan<<"\n";
  //cout << abs(ang) / w <<" "<< ans / w <<" "<< tan / v<<endl;
  return (abs(ang) + ans) / w + tan / v;
}
*/
