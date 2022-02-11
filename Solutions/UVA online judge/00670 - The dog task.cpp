#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=611

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }

};

db dist(const point& p1,const point& p2) {             
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 

vl match, vis;                                   // global variables
vector<vl> g;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : g[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while(t--)
    {
        
        ll V, Vleft;
        ll n, m;
        cin >> n >> m;
        vector<point> c, d;
        g.assign(n + m, vl());
        match.assign(n + m, -1);
        point p;
        for(int i = 0; i < n; i++)
        {

            cin >> p.x >> p.y;
            c.push_back(p);
        }
        for(int i = 0; i < m; i++)
        {
            cin >> p.x >> p.y;
            d.push_back(p);
        }
        for(int i = 0; i < n-1; i++)
        {
            db dis1 = dist(c[i], c[i+1]);
            for(int j = 0; j < m; j++)
            {
                db dis2 = dist(c[i], d[j]) + dist(d[j], c[i+1]);
               
                if(dis1 * 2 >= dis2)
                {

                    g[i].push_back(j + n);
                    g[j + n].push_back(i);
                }
            }
        }

        ll MCBM = 0;
        for(int L = 0; L < n; L++)
        {
            vis.assign(n, 0);
            MCBM += Aug(L);
        }
        vector<point> ans;
        for(int i = 0; i < n-1; i++)
        {
            ans.push_back(c[i]);
            for(int j = 0; j < m; j++)
                if(match[j + n] == i)
                    ans.push_back(d[j]);


        }
        ans.push_back(c[n-1]);
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++)
        {
            if(i) cout << " ";
            cout << ans[i].x << " " << ans[i].y;
        }cout << "\n";
        if(t) cout << "\n";

    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}