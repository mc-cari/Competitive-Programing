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

ll n, k;
bool o = 0;
vl f, f2, dis;
vector<vl> g;
ll ans = 0;


ll dfs(ll u, ll p)
{

	if(f[u])
	{
		return dis[u] = 0;
	}
	ll mini = INF;
	for(auto it : g[u])
	{
		if(it == p) continue;
		
		mini = min(dfs(it, u)+1, mini);
	}
	return dis[u] = mini;
}

void dfs2(ll u, ll p, ll d)
{

	if(d >= dis[u])
	{
		ans++;
		return;
	}
	for(auto it : g[u])
	{
		if(it == p) continue;
		dfs2(it, u, d+1);
	}
	if(g[u].size() == 1 && u !=0)
	{
		o = 0;
	}
	
}
 
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
    ll t;
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		ll x, y;
		ans = 0;
		f.assign(n, 0);
		o = 1;
		g.assign(n, vl());
		f2.assign(n, 0);
		dis.assign(n, INF);
		for(int i = 0; i < k; i++)
		{
			cin >> x;
			f[x-1] = 1;
		}
		for(int i = 0; i < n-1; i++)
		{
			cin >> x >> y;
			g[x-1].push_back(y-1);
			g[y-1].push_back(x-1);
		}
		dfs(0, -1);
		dfs2(0, -1, 0);

		if(!o)
		{
			cout << "-1\n";
			continue;
		}
		cout << ans << "\n";
	}
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}