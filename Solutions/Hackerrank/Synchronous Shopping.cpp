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
#define pb push_back

//https://www.hackerrank.com/challenges/synchronous-shopping/problem
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	srand((unsigned int) time(0));

	ll n, m, k, x, y, w;
	cin >> n >> m >> k;
	vl mask(n, 0);
	vector<vp> g(n, vp());

	for(int i = 0; i < n; i++)
	{
		cin >> x;
		ll msk = 0;
		for(int j = 0; j < x; j++)
		{
			cin >> y; y--;
			msk += (1 << y);
		}
		
		mask[i] = msk;
	}

	for(int i = 0; i < m; i++)
	{
		cin >> x >> y >> w;
		x--; y--;

		g[x].pb({w, y});
		g[y].pb({w, x});
	}

	
	

	vector<vl> d((1 << k), vl(n, INF));
	priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>> > q; //from low to high

	
	q.push({0, mask[0], 0});
	d[mask[0]][0] = 0;

	while(!q.empty()){

		ll w, u, msk;
		tie(w, msk, u) = q.top();
	    q.pop();
		
		if(w > d[msk][u])continue;
		for(auto it : g[u])
		{
			ll n_msk = msk | mask[it.second];
		   	if(d[n_msk][it.second] > w + it.first)
		   	{

		   		d[n_msk][it.second] = w + it.first;
		   		q.push({d[n_msk][it.second], n_msk, it.second});
			}
	    }
	}
	ll mini = INF;
	for(int i = 0; i < (1 << k); i++)
	{
		for(int j = 0; j < (1 << k); j++)
		{
			if((i | j) == (1 << k)-1) mini = min(mini, max(d[i][n-1], d[j][n-1]));

		}
		
	}
	cout << mini << "\n";
	

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
