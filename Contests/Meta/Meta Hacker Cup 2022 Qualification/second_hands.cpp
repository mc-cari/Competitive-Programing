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
		ll n, k, s;
		cin >> n >> k;
		set<ll> d1, d2;
		bool o = 1;
		rep(i, n) {
			cin >> s;
			if(d1.size() < d2.size()){
				if(!d1.count(s)){
					d1.insert(s);
				}
				else if(!d2.count(s)){
					d2.insert(s);
				}
				else o = 0;
			}
			else{
				if(!d2.count(s)){
					d2.insert(s);
				}
				else if(!d1.count(s)){
					d1.insert(s);
				}
				else o = 0;
			}
		}
		cout << "Case #" << T << ": ";
		if(!o || d1.size() > k || d2.size() > k) cout << "NO\n";
		else cout << "YES\n";

	}	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}