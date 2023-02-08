#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://open.kattis.com/problems/abstractart

struct point { db x, y;   
    point() { x = y = 0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& other) const
    {
        return (x < other.x ? true : (x == other.x && y < other.y));
    }
    bool operator == (const point& other) const
    {
        return abs(other.x - x) < EPS && abs(other.y - y) < EPS;
    }

    point operator + (const point& other) const
    {
        return point(x + other.x, y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(x - other.x, y - other.y);
    }
    point operator * (db other) const
    {
        return point(x * other, y * other);
    }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    point operator / (db other) const
    {
        return point(this->x / other, this->y / other);
    }

    point rot(){ return point(-y, x); }

  };
db dot(point a, point b)
{
  return a.x * b.x + a.y * b.y;
}
struct line { db a, b, c; };          

void pointsToLine(point p1, point p2, line &l) { 
  if (fabs(p1.x-p2.x) < EPS)                  
    l = {1.0, 0.0, -p1.x};                       
  else {
    db a = -(db)(p1.y-p2.y) / (p1.x-p2.x);
    l = {a,
         1.0,         
         -(db)(a*p1.x) - p1.y}; }
  }
bool areParallel(line l1, line l2) {       // check coefficients a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }
db cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > EPS; }

// returns the area
db area(const vector<point> &P) {
  db result = 0.0;
  for (ll i = 0; i < (ll)P.size()-1; i++)             // Shoelace formula
    result += P[i]^P[i+1]; // if all points are ll
  return result/2.0; }     // result can be ll(eger) until last step


bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;           
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                  p.y = -(l2.a*p.x + l2.c);
  return true; }

db dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

db norm_sq(vec v) { return v.x*v.x + v.y*v.y; } 

db angle(point a, point o, point b) {  
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }
bool inPolygon(point pt, const vector<point> &P) {
  if ((ll)P.size() < 3) return false;            
  db sum = 0;   
  for (ll i = 0; i < (ll)P.size()-1; i++) {
    if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);                  
    else sum -= angle(P[i], pt, P[i+1]); }                 
  return fabs(sum) > PI; }   

int orientation(point p, point q, point r) {
    ll tmp = cross(toVec(p, q), toVec(p, r));
    return tmp < 0 ? -1 : tmp == 0 ? 0 : 1; // sign
}
bool do_segments_intersect(point p1, point q1, point p2, point q2) {
    int o11 = orientation(p1, q1, p2);
    int o12 = orientation(p1, q1, q2);
    int o21 = orientation(p2, q2, p1);
    int o22 = orientation(p2, q2, q1);
    // oxx != 0 means cross intersection, no T intersection
    if (o11 != o12 && o21 != o22 && o11 != 0 && o12 != 0 && o21 != 0 && o22 != 0) // general case -> non-collinear intersection
        return true;
    return false;
}
db seg_integrate(point& a, point& b, db t1, db t2)
{
  // area
  point p1 = a + (b-a) * t1;
  point p2 = a + (b-a) * t2;
  return (p1^p2) / 2.0;
}

db param(point p1, point p2, point a)
{
  if(p1.x != p2.x)
  {
    db sgn = 1;
    if(p1.x > p2.x)sgn = -1;
    return (a.x - p1.x) / abs(p2.x - p1.x) * sgn;
  }
  db sgn = 1;
  if(p1.y > p2.y)sgn = -1;
  return (a.y - p1.y) / abs(p2.y - p1.y) * sgn;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, m;
    cin >> n;
    vector<vector< point> > pols(n, vector<point> ());
    db tot = 0;
    for(int i = 0; i < n; i++)
    {
      cin >> m;
      for(int j = 0; j < m; j++)
      {
        point p;
        cin >> p.x >> p.y;
        pols[i].push_back(p);
      }
      pols[i].push_back(pols[i][0]);
      db ax = area(pols[i]);
      if(ax < 0)
      {
        reverse(ALL(pols[i]));
        ax = -ax;
      }
      tot += ax;
      
    }
    db ans = 0;
    ll i1 = 0, i2 = 0;
    for(auto it : pols)
    {
      
      for(int i = 0; i < it.size()-1; i++)
      {
        ll cont = 0;
        vector<pair<db, db>>sweep;
        i2 = 0;
        for(auto it2 : pols)
        {
          if(it == it2){
            i2++;
            continue;
          }
          if(inPolygon(it[i], it2))cont++;
          for(int j = 0; j < it2.size()-1 ; j++)
          {
            line l1, l2;
            pointsToLine(it[i], it[i+1], l1);
            pointsToLine(it2[j], it2[j+1], l2);
            //not paralel
            if(abs((it[i+1] - it[i])^(it2[j+1] - it2[j])) > EPS && do_segments_intersect(it[i+1], it[i], it2[j+1], it2[j]))
            {
              point r;
              areIntersect(l1, l2, r);
              db t = param(it[i], it[i+1], r);
              db dir = 1;
              if(((it[i+1] - it[i])^(it2[j+1] - it[i])) < -EPS)dir = 0;
              if(t > -EPS && t < 1 + EPS)
                sweep.push_back({t, dir});
            } // colinear and same direction
            else if(abs((it[i+1] - it[i])^(it2[j+1] - it[i])) < EPS && abs((it[i+1] - it[i])^(it2[j] - it[i])) < EPS && dot((it[i+1] - it[i]),(it2[j+1] - it2[j])) > 0 && i1 < i2)// "z-index"
            {
              db t1 = param(it[i], it[i+1], it2[j]); 
              if(t1 > -EPS && t1 < 1 + EPS)
                sweep.push_back({t1, 0});
              db t2 = param(it[i], it[i+1], it2[j+1]); 
              if(t2 > -EPS && t2 < 1 + EPS)
                sweep.push_back({t2, 1});
            }
            
          }
          i2++;
        }
        db prev = 0;
        sort(ALL(sweep));
        if(sweep.size()){
          for(auto ir : sweep)
          {
            if(ir.second == 0)
            {
              if(cont == 0) ans += seg_integrate(it[i], it[i+1], prev, ir.first);
              cont++;
            }
            else
              cont--;
            prev = ir.first;
          }
          if(cont == 0) ans += seg_integrate(it[i], it[i+1], prev, 1);
        }
        else {
                bool contained = false;
                for(auto it4 : pols) if (it != it4 and inPolygon((it[i]+it[i+1])/2.0, it4)) {
                    contained = true; break;
                }
                if (!contained) ans += seg_integrate(it[i], it[i+1], 0, 1);
        }
      }
      i1++;
    }

    cout << fixed << setprecision(8) << tot << " " << ans  << "\n";


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
