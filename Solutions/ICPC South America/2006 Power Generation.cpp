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

//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=260&page=show_problem&problem=1658

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
  };

db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y); }

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n, c;
	 
    while(cin >> n >> c && (n + c))
    {
        ll x, y, p;
        vector<point>Q;
        vector<vl> g(n, vl());
        vl P;
        for(int i = 0; i < n; i++)
        {
            point d;
            cin >> d.x >> d.y >> p;
            P.push_back(p);
            if(!Q.empty())
            {
                ll mini = INF, id;
                for(int j = 0; j < i; j++)
                {
                    if(dist_sq(Q[j], d) < mini)
                    {
                        mini = dist_sq(Q[j], d);
                        id = j;
                    }
                }
                g[i].push_back(id);
            }
            Q.push_back(d);
        }
        ll ans = 0;
        for(int i = n-1; i >= 0; i--)
        {
            if(P[i] >= c)ans++;
            else if(i != 0)
            {
                P[g[i][0]] += P[i];
            }
            
        }
        cout << ans << "\n";
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
