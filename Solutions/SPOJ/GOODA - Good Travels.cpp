#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/GOODA/

#define rep(i,a,b) for(ll i=a; i<=b; ++i)
vl fun, acum, id;
ll in = 0;
struct tarjanSCC {
    vector<ll> _stack, ids, low;
    vector<bool> instack;
    vector<vector<ll>>* g;
    ll n, ID;
    void dfs(ll u) {
        ids[u] = low[u] = ID++;
        instack[u] = true;
        _stack.push_back(u);
        for (ll v : (*g)[u]) {
            if (ids[v] == -1) {
                dfs(v);
                low[u] = min(low[v], low[u]);
            } else if (instack[v]) {
                low[u] = min(low[v], low[u]);
            }
        }
        if (low[u] == ids[u]) {

            while (1) {
                ll x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                acum[in] += fun[x];
                id[x] = in;
                if (x == u) break;
            }
            in++;

        }
    }
    tarjanSCC(vector<vector<ll>>& _g) {
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


vector<set<ll> > g2;
ll S, E;
void dfs(ll ind, vector<vector<ll> >& g)
{
  for(auto it: g[ind])
    if(id[it] != id[ind])
      g2[id[ind]].insert(id[it]);
  return;
  
}

ll memo[1000015];
ll dp (ll in)
{
  if(in == id[E]) return acum[in];
  if(memo[in] != -1) return memo[in];
  ll ans = 0, cont = 0;
  for(auto it : g2[in])
  {
    ans = max(ans, dp(it));
    cont++;
  }
  if(!cont)return memo[in] = -INF;
  return memo[in] = ans + acum[in];

}

int main() {
    ios_base:: sync_with_stdio(0);
    cin.tie(0);
    ll n, m, x; cin >> n >> m >> S >> E;
    E--;
    S--;
    vector<vector<ll>> g(n);
    acum.assign(n, 0);
    for(ll i = 0; i < n; i++)
    {
      cin >> x;
      fun.push_back(x);
    }
    while(m--) {
        ll u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
    }
    id.assign(n, 0);
    tarjanSCC tscc(g);
    g2.assign(n, set<ll>());
    for(ll i = 0; i < n; i++)
      dfs(i, g);
    memset(memo, -1, sizeof(memo));
    cout<<dp(id[S])<<"\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}
