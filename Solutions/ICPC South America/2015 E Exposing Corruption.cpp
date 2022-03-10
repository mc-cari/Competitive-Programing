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

//https://www.urionlinejudge.com.br/judge/es/problems/view/2008
int knapSack(int W, vl wt, vl val, int n)
{
   ll K[n+1][W+1];
   for (int i = 0; i <= n; i++)
   {
       for (int w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }

   return K[n][W];
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	ll D, P, R, B;
	cin >> D >> P >> R >> B;
	vl c;
	vector<vl> g(D + P, vl(0));
	ll x, y;
	for(int i = 0; i < D; i++)
	{
		cin >> x;
		c.push_back(x);
	}
	for(int i = 0; i < P; i++)
	{
		cin >> x;
		c.push_back(x);
	}
	for(int i = 0; i < R; i++)
	{
		cin >> x >> y;
		g[x-1].push_back(D + y - 1);
		g[D + y - 1].push_back(x - 1);
	}
	vl v(D + P, 0), v1, v2, w;
	ll n = 0;
	for(int i = 0; i < D + P; i++)
	{
		ll cost = 0, d = 0, p = 0;
		if(v[i])continue;
		stack<ll> q;
		q.push(i);
		while(!q.empty()){

			ll t = q.top();
			
			
			q.pop();
			if(!v[t]){
				cost += c[t];
				if(t < D)
					d++;
				else
					p++;

				v[t]=1;
				for(ll i=0;i<g[t].size();i++){

					if(!v[g[t][i]])
					{
						q.push(g[t][i]);
					}
				}
			}
		}
		w.push_back(cost);
		v1.push_back(p - d);
		v2.push_back(d - p);
		n++;
	}
	ll ans1 = knapSack(B, w, v1, n) + D, ans2 = knapSack(B, w, v2, n) + P;
	cout << ans1 << " " << ans2 << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
