#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/problemset/problem/350/D

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
    ll operator^(const point &p) const {return x * p.y - y * p.x; }
    point operator / (db other) const
    {
        return point(this->x / other, this->y / other);
    }

    point rot(){ return point(-y, x); }

  };
db dist_sq(point& p1, point& p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }
struct line { 
  db a, b, c;

  bool operator < (const line &l) const
  {
      if (a != l.a)
        return a < l.a;
      if (b != l.b)
          return b < l.b;
      return c < l.c;
  }
 };        

void pointsToLine(point& p1, point p2, line &l) { 
  l.a = p1.y - p2.y;
  l.b = p2.x - p1.x;
  l.c = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
  ll sgn = 1;
  if(l.a < 0 || (l.a == 0 && l.b < 0))sgn = -1;
  ll g = __gcd(abs(l.a), __gcd(abs(l.b), abs(l.c))) * sgn;
  
  l.a /= g; l.b /= g; l.c /= g;
}

struct cirs { 
  point p;
  db r;
  
 };

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, m;
    cin >> n >> m;
    point p, q;
    cirs cir[1501];
    map<line, vl > ml, mr;
    for(int i = 0; i < n; i++)
    {
        cin >> p.x >> p.y;
        cin >> q.x >> q.y;
        q = q*2;
        p = p*2;
        if(q < p)swap(p, q);
        line l;
        pointsToLine(p, q, l);
        ml[l].push_back(p.x);
        mr[l].push_back(q.x);
    }
    for(auto& it : ml)
      sort(ALL(it.second));
    for(auto& it : mr)
      sort(ALL(it.second));
    for(int i = 0; i < m; i++)
      cin >> cir[i].p.x >> cir[i].p.y >> cir[i].r;
    ll ans = 0;
    for(int i = 0; i < m; i++)
    {
      for(int j = i + 1; j < m; j++)
      {
        if(cir[i].r == cir[j].r && dist_sq(cir[i].p, cir[j].p) > 4*cir[i].r*cir[j].r)
        {
          point s = (cir[i].p + cir[j].p), t = (cir[j].p - cir[i].p).rot();
          line l;
          pointsToLine(s, s + t, l);
          if(!mr.count(l))continue;
          ans += mr[l].size();
          ans -= lower_bound(ALL(mr[l]), s.x) - mr[l].begin();
          ans -= ml[l].end() - upper_bound(ALL(ml[l]), s.x);
        }
        
      }
    }
    cout << ans << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
