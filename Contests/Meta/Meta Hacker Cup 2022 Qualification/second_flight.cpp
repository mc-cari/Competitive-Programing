#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e17
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));
	ll t;
	cin >> t;
	repx(T, 1, t+1){
		
		ll n, m, q;
		cin >> n >> m >> q;
		vector<vp> g(n, vp(0));
		vector<vl> big;
		vl ids(n, -1);
		vector<unordered_map<ll, ll>> nex(n, unordered_map<ll, ll>());
		rep(i, m){
			ll a, b, c;
			cin >> a >> b >> c;
			g[a-1].pb({b-1, c});
			g[b-1].pb({a-1, c});
			nex[a-1][b-1] = c;
			nex[b-1][a-1] = c;
		}
		rep(i, n){
			if(g[i].size()*g[i].size() >= n){
				ids[i] = big.size();
				vl aux(n, 0);
				for (auto it : g[i])
					for(auto it2 : g[it.first]){
						aux[it2.first] += min(it.second, it2.second);
					}
				big.pb(aux);
			}
		}
		cout << "Case #" << T << ": ";
		rep(_, q){
			ll x, y;
			cin >> x >> y;
			x--; y--;
			if(ids[y] != -1) swap(x, y);
			if(ids[x] != -1){
				cout << nex[x][y] * 2 + big[ids[x]][y] << " ";
			}
			else{
				ll ans = nex[x][y] * 2;
				for (auto it : g[x])
					ans += min(it.second, nex[it.first][y]);
				cout << ans << " ";
			}
		}cout << "\n";
	}
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}