#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/problemset/problem/427/C

#define rep(i,a,b) for(int i=a; i<=b; ++i)
vl cost;
ll ways = 1, ans = 0, M = 1000000007;
// -----------------------------------------
// implementation of Tarjan's SCC algorithm
struct tarjanSCC {
    vector<int> _stack, ids, low;
    vector<bool> instack;
    vector<vector<int>>* g;
    int n, ID;
    void dfs(int u) {
        ids[u] = low[u] = ID++;
        instack[u] = true;
        _stack.push_back(u);
        for (int v : (*g)[u]) {
            if (ids[v] == -1) {
                dfs(v);
                low[u] = min(low[v], low[u]);
            } else if (instack[v]) {
                low[u] = min(low[v], low[u]);
            }
        }
        if (low[u] == ids[u]) {

            ll cont = 0, mini = INF;
            while (1) {
                int x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                if(cost[x] < mini)
                {
                  mini = cost[x];
                  cont = 1;
                }
                else if(cost[x] == mini)cont++;

                if (x == u) break;
            }
            ans += mini;
            ways *= cont;
            ways %= M;

        }
    }
    tarjanSCC(vector<vector<int>>& _g) {
        g = &_g;
        n = _g.size();
        _stack.reserve(n);
        ids.assign(n, -1);
        low.resize(n);
        instack.assign(n, 0);
        ID = 0;
        rep(u, 0, n-1) if (ids[u] == -1) dfs(u);
    }
};

// example of usage
int main() {
    // read and build graph from standard input
    int n, m, x; cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n; i++)
    {
      cin >> x;
      cost.push_back(x);
    }
    cin >> m;
    while(m--) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
    }
    // find SCCs
    tarjanSCC tscc(g);
    cout<<ans<<" "<<ways<<"\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}
