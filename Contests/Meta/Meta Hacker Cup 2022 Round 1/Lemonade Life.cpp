#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF LLONG_MAX
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)


struct point { ll x, y;   
    point() { x = y = 0.0; }                      
    point(ll _x, ll _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }

  };

bool ccw(point p, point q, point r) {
  return ((q - p)^(r - p)) > 0; }

void CH_Andrew(vector<point> &Pts, vector<point> &H) {
  ll n = Pts.size(), k = 0;
  H.resize(2*n);
  sort(Pts.begin(), Pts.end());        // sort the points lexicographically
  for (ll i = 0; i < n; i++) {                         // build lower hull
    while (k >= 2 && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  for (ll i = n-2, t = k+1; i >= 0; i--) {             // build upper hull
    while (k >= t && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  H.resize(k);

}

db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll t;
	cin >> t;
    
	repx(T, 1, t+1){
        
		ll N, K, D;
		cin >> N >> K >> D;

        vector<point> Pts, H;
		rep(i, N) {
            point p;
            cin >> p.x >> p.y;
            Pts.pb(p);
        }

        CH_Andrew(Pts, H);
        H.pop_back();

        ll maxid = 0;
        N = H.size();
        rep(i, N) if(H[i].x > H[maxid].x) maxid = i;

        vl d(N, INF);
        d[0] = 0;
        vl m(N, 2);
        deque<ll> q;
        q.push_back(0);

        while (!q.empty()) {
            int u = q.front();

            if(H[u].x > H[maxid].x) maxid = u;
            q.pop_front();
            m[u] = 0;
            rep(it, N){
                ll cost = max(K, (H[it].x - H[u].x)*(H[it].x - H[u].x) + (H[it].y - H[u].y)*(H[it].y - H[u].y));
                if (d[it] > d[u] + cost && dist_sq(H[u], H[it]) <= D*D) {
                    d[it] = d[u] + cost;
                    if (m[it] == 2) {
                        m[it] = 1;
                        q.push_back(it);
                    } else if (m[it] == 0) {
                        m[it] = 1;
                        q.push_front(it);
                    }
                }
            }
        }
        if(d[maxid] == INF) d[maxid] = -1;
		cout << "Case #" << T << ": " << d[maxid] << "\n";
	}
	
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}