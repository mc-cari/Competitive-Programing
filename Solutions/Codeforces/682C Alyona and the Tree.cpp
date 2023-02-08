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

ll n;
vl a;
vector<vp> g;

ll dfs(ll in, ll dp)
{
    if(a[in] < dp) return 0;
    ll ans = 1;
    for(auto it : g[in])

        ans += dfs(it.first, it.second + max(0LL, dp));

    return ans;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

    ll x, y;
    cin >> n;
    a.clear();

    for(int i = 0; i < n; i++)
    {
        cin >> x;
        a.push_back(x);
    }
    g.assign(n, vp());
    for(int i = 0; i < n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back({i+1, y});
    }

    cout << n - dfs(0, 0) << '\n';
    


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}