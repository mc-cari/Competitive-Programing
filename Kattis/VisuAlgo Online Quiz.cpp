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

//https://open.kattis.com/problems/visualgo

vector <vl > g2;
ll s, t;

ll memo[10005];
ll dp(ll i)
{
    if(i == t)return 1;
    if(memo[i] != -1)return memo[i];

    ll ans = 0;
    for(auto it : g2[i])
        ans += dp(it);

    return memo[i] = ans;
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;

	vector< vp > g(n, vp (0));
    g2.assign(n, vl (0));
	vl d(n, INF);
    memset(memo, -1, sizeof (memo));

    
	for(ll i = 0; i < m; i++)
	{
		ll u, v, w;
		cin >> u >> v >> w;
		
		g[u].push_back({w, v});
	}

    cin >> s >> t;
    deque<ll> q;
	q.push_back(s);
	d[s] = 0;
    vl M(n, 2);

	while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        M[u] = 0;
        for (auto it : g[u]) {
            if (d[it.second] > d[u] + it.first) {
                d[it.second] = d[u] + it.first;
                if (M[it.second] == 2) {
                    M[it.second] = 1;
                    q.push_back(it.second);
                } else if (M[it.second] == 0) {
                    M[it.second] = 1;
                    q.push_front(it.second);
                }
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(auto it : g[i])
        {
            if(d[i] + it.first == d[it.second])
                g2[i].push_back(it.second);  
        }

    }
    cout << dp(s) << "\n";
    
    

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
