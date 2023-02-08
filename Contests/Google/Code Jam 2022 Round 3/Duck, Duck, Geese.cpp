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
			vl c, vis(N, 0), d(N, 1);
			ll color = 1;
			for(int i = 0; i < N; i++)
			{
				cin >> x;
				c.push_back(x);
				
			}
			for(int i = N-1; i >= 0; i--)
			{
				x = c[i];
				if(x-1 == i)
				{
					d[i] = color;
					color++;
				}
				else if(!vis[i] && !vis[x-1])
				{
					vis[i] = 1;
					vis[x-1] = 1;
					d[i] = color;
					d[x-1] = color;
					color++;
				}
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