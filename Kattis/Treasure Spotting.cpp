#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e7
#define EPS 0.0000000001
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const db PI = acos(-1.0);

//https://open.kattis.com/problems/treasurespotting

struct point { db x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(db _x, db _y) : x(_x), y(_y) {}        // user-defined
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
        return point(this->x + other.x, this->y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }
    point operator * (long double other) const
    {
        return point(this->x * other, this->y * other);
    }

    point operator / (long double other) const
    {
        return point(this->x / other, this->y / other);
    }

    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };
struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

db dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

db norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }

db angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }




//Constant values to be returned
constexpr int Colinear = -1, NoIntersect = 0, Intersect = 1;
constexpr int CW = 2, CCW = 3;
constexpr int Inside = 4, Outside = 5, OnEdge = 6;

long double cross(const point& A, const point& B, const point& C)
{
    point AB = B - A, AC = C - A;
    return(AB.x * AC.y - AB.y * AC.x);
}

//Finds orientation of triplet of points p, q, r
//Returns Colinear, CW, or CCW
int orientation(const point& p, const point& q, const point& r)
{
    long double val = cross(p, q, r);
    if(abs(val) < EPS) return Colinear;
    return (val > 0) ? CW : CCW;
}

//Container for line segment
struct segment { point p1, p2; 
  segment(point _p1, point _p2) : p1(_p1), p2(_p2) {}
};

//Checks if point p is possibly on the segment s
//but doesn't guarantee it is
bool onSegment(const point& p, const segment& s)
{
    bool x = (abs(s.p1.x - s.p2.x) < EPS && abs(p.x - s.p2.x) < EPS) || (p.x <= max(s.p1.x, s.p2.x) && p.x >= min(s.p1.x, s.p2.x));
    bool y = (abs(s.p1.y - s.p2.y) < EPS && abs(p.y - s.p2.y) < EPS) || (p.y <= max(s.p1.y, s.p2.y) && p.y >= min(s.p1.y, s.p2.y));
    return x && y;
}

//Returns of list of intersection points between segments s1, and s2
//If they do not intersect, the result is an empty vector
//If they intersect at exactly 1 point, the result contains that point
//If they overlap for non-0 distance, the left and right points of that intersection
//  are returned
vector<point> intersect(const segment& s1, const segment& s2)
{

    point a = s1.p1, b = s1.p2, c = s2.p1, d = s2.p2;

    if(orientation(a, b, c) == Colinear && orientation(a, b, d) == Colinear &&
        orientation(c, d, a) == Colinear && orientation(c, d, b) == Colinear)
    {
        point min_s1 = min(a, b), max_s1 = max(a, b);
        point min_s2 = min(c, d), max_s2 = max(c, d);

        if(max_s1 < min_s2 || max_s2 < min_s1) return {};

        point start = max(min_s1, min_s2), end = min(max_s1, max_s2);
        if(start == end)
            return {start};
        else
            return {min(start, end), max(start, end)};
    }

    long double a1 = b.y - a.y, a2 = d.y - c.y;
    long double b1 = a.x - b.x, b2 = c.x - d.x;
    long double c1 = a1*a.x + b1*a.y, c2 = a2*c.x + b2*c.y;
    long double det = a1*b2 - a2*b1;
    if(abs(det) > EPS)
    {
        point inter((b2*c1 - b1*c2)/det, (a1*c2 - a2*c1)/det);

        if(onSegment(inter, s1) && onSegment(inter, s2))
            return {inter};
    }
    return {};
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    db W, P;
    cin >> W >> P;
    point p1, p2, s;
    db x, y;
    cin >> s.x >> s.y;

    vector<pair<point, point> >walls, piras;
    for(int i = 0; i < W; i++)
    {
      cin >> p1.x >> p1.y;

      cin >>p2.x >> p2.y;

      walls.push_back({p1, p2});
    }
    for(int i = 0; i < P; i++)
    {
      cin >> p1.x >> p1.y;

      cin >> p2.x >> p2.y;

      piras.push_back({p1, p2});
    }
    
    for(int i = 0; i < P; i++)
    {

      bool o = 1;
      for(int j = 0; j < W; j++)
      {
        segment s1(piras[i].first, s);
        segment s2(walls[j].first, walls[j].second);
        vector <point> ps = intersect(s1, s2);
        if(ps.size() > 0)
          o = 0;
      }

      if(dist_sq(piras[i].first, s) > dist_sq(piras[i].first, piras[i].second))o = 0;

      if(!(dot(toVec(s, piras[i].first), toVec(piras[i].second, piras[i].first)) > - EPS))o = 0; 

      for(int j = 0; j < P; j++)
      {
        if(j == i)continue;
        segment s1(piras[i].first, s);
        segment s2(piras[j].first, piras[j].first);
        vector <point> ps = intersect(s1, s2);
        if(ps.size() > 0)
          o = 0;
      }

      if(!o)cout<<"not visible\n";
      else cout<<"visible\n";
    }
    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
