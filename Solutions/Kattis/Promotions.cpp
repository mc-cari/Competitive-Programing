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

// https://open.kattis.com/problems/promotions

vl vis;
ll dfs(ll u, vector<vl>& g)
{
    if(vis[u]) return 0;
    vis[u] = 1;
    ll cont = 1;
    for(auto it : g[u])
        cont += dfs(it, g);
    return cont;
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<vl > g, invg;
    ll A, B, P, E, x, y;
	cin >> A >> B >> E >> P;
	g.assign(E, vl(0));
    invg.assign(E, vl(0));
    vis.assign(E, 0);
	for(int i = 0; i < P; i++)
    {
        cin >> x >> y;
        g[x].push_back(y);
        invg[y].push_back(x);
    }
    ll cant = 0, ans1 = 0, ans2 = 0;
    for(int i = 0; i < E; i++)
    {
        vis.assign(E, 0);
        if(dfs(i, invg) > B)cant++;
        vis.assign(E, 0);
        ll not_need = dfs(i, g);

        if(E - not_need + 1 <= A) ans1++;
        if(E - not_need + 1 <= B) ans2++;
    }
    cout << ans1 << "\n";
    cout << ans2 << "\n";
    cout << cant << "\n";




    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
