#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,ll>
#define rep(i, n) for(int i = 0; i<(int)n; ++i)


int main(){
  int n, m;
  cin >> n >> m;


  vector<vector<pll>> g(n, vector<pll>());

  rep(i, m)
  {
    int u, v, c;
    cin >> u >> v >> c;
    g[u].pb({c, v});
  }  

  int l = 0, r = 1e9, res = -1;
  while(l <= r)
  {
    int p = (l + r) / 2;

    vector<int>V(n, 0);
    bool o = 0;

    rep(i, n){
      if(V[i]) continue;

      stack<int>s;
      

      s.push(i);

      while(!s.empty())
      {
        int v = s.top();
        s.pop();
        if(V[v]) continue;
        V[v] = 1;

        for (auto [c, u] : g[v]){
          if(c <= p) continue;
          if(V[u] == 1)
            o = 1;
          else
            s.push(u);
        }
      }
    }

    if(o){
      r = p-1;
      res = p;
    }
    else
      l = p+1;


  }


}