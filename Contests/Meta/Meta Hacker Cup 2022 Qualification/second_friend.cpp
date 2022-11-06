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

	vl dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
	repx(T, 1, t+1){
		ll r, c;
		cin >> r >> c;
		char g[r][c], g2[r][c];
		vector<vl> cont(r, vl(c, 0));
		stack<pll> s;
		rep(i, r) rep(j, c) {
			cin >> g[i][j];
			g2[i][j] = g[i][j];
			if(g2[i][j] == '^')g2[i][j] = '.';
		}

		rep(i, r) rep(j, c){
			if(g[i][j] == '#') continue;
			rep(k, 4)
			{
				ll x = i + dx[k], y = j + dy[k];
				if(x >= 0 && x < r && y >= 0 && y < c && g[x][y] != '#') cont[x][y]++;
				
			}
		}

		rep(i, r) rep(j, c) if(cont[i][j] < 2) s.push({i, j});
		while(!s.empty()){
			ll i, j;
			tie(i, j) = s.top();
			s.pop();

			rep(k, 4)
			{
				ll x = i + dx[k], y = j + dy[k];
				if(x >= 0 && x < r && y >= 0 && y < c && g[i][j] != '#') {
					if(cont[x][y] == 2) s.push({x, y});
					cont[x][y]--;
				}
			}
		}

		rep(i, r) rep(j, c)  if(cont[i][j] >= 2) g2[i][j] = '^';
		bool o = 1;
		rep(i, r) rep(j, c)  if(g[i][j] == '^' && g2[i][j] != '^') o = 0;
		cout << "Case #" << T << ": ";
		if(!o) cout << "Impossible\n";
		else {
			cout << "Possible\n";
			rep(i, r){
				rep(j, c) cout << g2[i][j];
				cout << "\n";
			}
		}

		

	}	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}