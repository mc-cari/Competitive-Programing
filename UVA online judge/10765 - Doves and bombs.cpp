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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1706

#define ff first
#define ss second
typedef pair<int,int> ii;
vector<int> D, L, vis;
vector<vl> g;
stack<ii> s; 
vl comps;
ll root = 0;

void print_and_remove_bicomp(int u, int v) {

    ii uv(u,v);
    unordered_map<int,int> mp;
    while (true) {
        ii top = s.top(); s.pop();
        if(!mp[top.ff]) {
            mp[top.ff] = 1;
            comps[top.ff]++;
        }
        if(!mp[top.ss]) {
            mp[top.ss] = 1;
            comps[top.ss]++;
        }

        if (top == uv) break;
    }
}


// find biconnected components
void dfs(int u, int p, int d) {
    D[u] = L[u] = d;
    vis[u] = 1;

    for(auto v : g[u]) {
        if (v == p) continue;
        
        if (D[v] == -1) {
            s.emplace(u,v);
            dfs(v, u, d+1);
            if (p == -1 || L[v] >= d) print_and_remove_bicomp(u,v);
            L[u] = min(L[u], L[v]); 
        } else if (D[v] < d) {
            s.emplace(u,v);
            L[u] = min(L[u], D[v]);
        }
    }
}
int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, m;
    while(cin >> n >> m && n + m > 0)
    {
        g.assign(n, vl());
        vis.assign(n, 0);
        L.assign(n, 0);
        D.assign(n, -1);
        ll x, y;
        comps.assign(n, 0);
        while(cin >> x >> y && x + y != -2)
        {
            g[x].push_back(y);
            g[y].push_back(x);
        }
        vp ans;
        for(int i = 0; i < n; i++)
        {
            if(!vis[i])
                dfs(i, -1, 0);
            ans.push_back({comps[i], -i});

        }
        sort(ALLR(ans));
        for(int i = 0; i < m; i++)
        {
            cout << -ans[i].second << " " << ans[i].first << "\n";
        }cout << "\n";
        
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
