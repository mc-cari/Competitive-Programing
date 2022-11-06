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

//https://codeforces.com/contest/1704/problem/E

ll M = 998244353;

vl s, v, val;
vector<vl > g;
void dfs(int t)
{
    v[t] = 1;
    for(auto it : g[t]){

        if(!v[it])
            dfs(it);
    }
    s.push_back(t);
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));
	ll t;
	cin >> t;
	while(t--){

		ll n, m;
		cin >> n >> m;
		g.assign(n, vl());
		v.assign(n, 0);
		val.assign(n, 0);
		s.clear();
		vl v2(n, 0);
		rep(i, n) cin >> val[i];
		rep(i, m){
			ll x, y;
			cin >> x >> y;
			g[x-1].pb(y-1);
		}

		//sim
		ll time = 0;
		rep(i, n){
			bool o = 0;
			rep(j, n){
				if(val[j]){
					o = 1;
					v2[j] += val[j]-1;
					if(v2[j] >= M) v2[j] = v2[j] % M + M;
					for(auto it : g[j]){
						v2[it]++;
						if(v2[it] >= M) v2[it] = v2[it] % M + M; 
					}
				}
			}
			val = v2;
			v2.assign(n, 0);
			if(!o)break;
			time++;


		}
		if(time != n){
			cout << time << "\n";
			continue;
		}
		

		for(int i = 0; i < n; i++)
			if(!v[i])
				dfs(i);

		reverse(ALL(s));

		
		for(auto it : s){
			for(auto it2 : g[it]){
				val[it2] += val[it];
				val[it2] %= M;
			}
		}
		
		cout <<  (val[s.back()] + n)%M << "\n";
	}
	
	

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
