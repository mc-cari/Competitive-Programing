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

ll M = 1e9 + 7;

ll solve(vp& sweep){
	sort(ALL(sweep));
	ll tam = 0, ac = 0, tot = 0, prev = sweep[0].first, ans = 0;
	for(auto it : sweep){


		ll k = it.first - prev;
		prev = it.first;
		tot += (2*k*ac)%M + ((k*k)%M)*tam%M;
		tot %= M;

		ac += k * tam;
		ac %= M;

		if(it.second == 1)
			tam++;

		else
			ans = (ans + tot)%M;
	}
	return ans;
}
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll t;
	cin >> t;
	repx(T, 1, t+1){

		ll N, Q, x, y, ans = 0;
		vp sweep1, sweep2, sweep3, sweep4;
		cin >> N;
		rep(i, N){
			cin >> x >> y;
			sweep1.pb({x, 1});
			sweep2.pb({1e9 - x, 1});
			sweep3.pb({y, 1});
			sweep4.pb({1e9 - y, 1});
		}

		cin >> Q;
		rep(i, Q){
			cin >> x >> y;
			sweep1.pb({x, 2});
			sweep2.pb({1e9 - x, 2});
			sweep3.pb({y, 2});
			sweep4.pb({1e9 - y, 2});
		}

		

			//cout << it.first << " " << it.second << " " << tot << " " << ac << " " << tam << "\n";
		ans += solve(sweep1);
		ans %= M;
		ans += solve(sweep2);
		ans %= M;
		ans += solve(sweep3);
		ans %= M;
		ans += solve(sweep4);
		ans %= M;

		cout << "Case #" << T << ": " << ans << "\n";
		
	}
	
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}