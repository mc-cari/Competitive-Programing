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
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2870
stack<int> St;
int cont, numSCC;
vl dfs_num, dfs_low, visited, comp; 
vector<vl> g;
void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = cont;    
  cont++;                            
  St.push(u);                                   
  visited[u] = 1;
  for (auto v : g[u]) {
    if (dfs_num[v] == -1)
      tarjanSCC(v);
    if (visited[v])                             
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }

  if (dfs_low[u] == dfs_num[u]) {              
    //cout << "found:\n";                     
    while (1) {
      int v = St.top(); St.pop(); visited[v] = 0;
      comp[v] = numSCC;
      //cout << v << " ";
      if (u == v) break;
    }
    //cout << "\n numSCC: " << numSCC << endl;
    ++numSCC;  
  }
}



int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    for(int T = 1; T <= t; T++)
    {
        ll n, m, x, y;
        cin >> n >> m;
        g.assign(n, vl());
        comp.assign(n, 0);
        
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y;
            x--; y--;
            g[x].push_back(y);
        }
        dfs_num.assign(n, -1); dfs_low.assign(n, 0); visited.assign(n, 0);
        while (!St.empty()) St.pop();
        cont = numSCC = 0;
        for (int u = 0; u < n; ++u)
            if (dfs_num[u] == -1)
                tarjanSCC(u);

        vl indegree(numSCC, 0);
        for(int i = 0; i < n; i++)
        {
            unordered_map<ll, ll> mp;
            for(auto it : g[i])
            {
                if(comp[i] != comp[it] && !mp[comp[it]])
                {
                    mp[comp[it]] = 1;
                    indegree[comp[it]]++;
                    
                }
            }
        }
        ll ans = 0;
        for(int i = 0; i < numSCC; i++)
        {
            if(indegree[i] == 0)
                ans++;
        }
        cout << "Case " << T << ": " << ans << "\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
