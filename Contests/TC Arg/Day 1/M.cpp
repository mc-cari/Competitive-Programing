#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define ll long long
#define ull unsigned long long
#define vl vector<ll> 
#define rep(i, n) for(int i = 0; i<(int)n; ++i)
#define repx(i, a, b) for(int i = (int)a; i < (int)b; i++)
ll maxlog2(ll x)
{
  return (63 - __builtin_clzll(x));
}

struct SparseTableLCA
{
  ll maxlg;
  vector<vl> SP;
  vl D;

  SparseTableLCA(vector<vl>& g, vl& ini)
  {
    ll n = g.size();
    vl vis(n,0), parent(n, -1);
    D.resize(n, 1e9);
    queue<ll>q;
    for(auto it : ini)
    {
      D[it]=0;
      q.emplace(it);
    }

    while(!q.empty()){
      ll k=q.front();q.pop();
      if(!vis[k])
      {
        vis[k]=1;
        for(auto it : g[k])
          if(!vis[it])
          {
            parent[it]=k;
            D[it]=D[k]+1;
            q.push(it);
          }
      }
    }
    SP.clear();
    SP.push_back(parent);
    maxlg = 63 - __builtin_clzll(n);

    repx(i, 1, maxlg+1)
    {
      vl aux;
      rep(j, n)
      {
        if(SP[i-1][j]!=-1)
        aux.push_back(SP[i-1][SP[i-1][j]]);
        else aux.push_back(-1);
      }
      SP.push_back(aux);
    }
  }

  ll level(ll a, ll n)
  {
    while(D[n] != a)
      n = SP[maxlog2(D[n]-a)][n];
    return n;
  }

  ll LCA(ll u, ll v)
  {
    ll x = u, y = v;
    if(D[u] <= D[v]) swap(x, y);

    if(D[x] != D[y])
      x = level(min(D[x], D[y]), x);

    if(x == y) return x;

    for(ll i =maxlg ; i >=0; i--)
    {
      if(SP[i][x] != SP[i][y] && SP[i][x] != -1)
      {
        x = SP[i][x];
        y = SP[i][y];
      }
    }
    return SP[0][x];
  }
};


int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);

  int N, Q;
  
  cin >> N >> Q;
  vector<vl>g(N, vl());
  vl ini(N, 0), iniNodes;

  rep(i, N)
  {
    ll a;
    cin >> a;

    if(a != -1){
      g[a].push_back(i);
      ini[i] = 1;
    }
  }

  rep(i, N)
    if(ini[i] == 0)
      iniNodes.push_back(i);

  SparseTableLCA lca(g, iniNodes);
  
  rep(i, Q)
  {
    int x, y;
    cin >> x >> y;
    //cout << lca.LCA(x, y) << endl;
    if(lca.D[x] >= lca.D[y] && lca.LCA(x, y) == y)
      cout << "Yes\n";
    else cout << "No\n";

  }
}