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


int main(){

	//ios_base::sync_with_stdio(0);
	//cin.tie(0);

	ll T, N, K;
	cin >> T >> N >> K;
	for(int t = 1; t <= T; t++)
	{
		ll resp = 0;

		while(resp != 1 && resp != -1){
			ll x;
			vl c, vis(N, 0), d(N, N);
			ll color = 1;
			for(int i = 0; i < N; i++)
			{
				cin >> x;
				c.push_back(x-1);
			}
			vector<vl>g;
			for(int i = 0; i < N; i++)
			{
				if(!vis[i])
				{
					vl aux = {i};
					vis[i] = 1;
					ll in = c[i];
					while(in != i)
					{
						aux.push_back(in);
						vis[in] = 1;
						in = c[in];
					}
					g.push_back(aux);
				}
			}
			for(auto it : g)
			{
				ll cont = 0;
				for(auto it2: it)
				{
					d[it2] = color;
					cont++;
					if(cont == 2)
					{
						cont = 0;
						color++;
					}
				}
				color++;
			}

			for(int i = 0; i < N; i++)
			{
				cout << flush << d[i];
				if(i < N-1) cout << flush << " ";
				else cout << flush << "\n";
			}
			cin >> resp;
			if(resp == 1 || resp == -1) break;
		}
		if(resp == -1)break;

	}

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}