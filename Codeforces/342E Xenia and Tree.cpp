#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

https://codeforces.com/problemset/problem/342/E

ll maxlog2(ll x){
    return (63 - __builtin_clzll(x));
}
vl D;// LCA depht
struct SparseTableLCA
{
    ll maxlg;
    vector<vl >SP;
    vector<vl >MN;
    SparseTableLCA(vl&A)
    {
        ll n=A.size();
        SP.clear();
        SP.push_back(A);
        ll maxlog = 63 - __builtin_clzll(n);
        maxlg=maxlog;
        for(ll i=1;i<=maxlog;i++)
        {
            vl c;
            for(ll j=0;j<n;j++)
            {
                if(SP[i-1][j]!=-1)
                c.push_back(SP[i-1][SP[i-1][j]]);
                else c.push_back(-1);
            }
            SP.push_back(c);
        }
    }
    ll level(ll a,ll n)// a=distancia
    {
        while(D[n]!=a)
        {
            n=SP[maxlog2(D[n]-a)][n];
        }
        return n;
    }
    ll LCA(ll u,ll v)
    {
        ll x,y;
        if(D[u]>D[v])
        {
            x=u;y=v;
        }
        else
        {
           x=v;y=u;
        }
        if(D[x]!=D[y]){
            x = level(min(D[x],D[y]),x);
        }
        if(x==y)return x;
        for(ll i = maxlg;i>=0;i--)
        {
            if(SP[i][x]!=SP[i][y]&&SP[i][x]!=-1)
            {
                x=SP[i][x];
                y=SP[i][y];
            }
        }
        return SP[0][x];
    }
    ll Dist(ll u,ll v)
    {
        return D[u]+D[v]-2*D[LCA(u,v)];//-1??
    }
};

vl siz;
vector<bool> passed;
vl depht;
vector<vl>CTree;
vl parent;
vl ans;

ll get_centroid(ll in, vector<vl>& g, vl& siz, vector<bool>& vis, ll tam)
{
    ll maxi=0, imaxi;
    vis[in]=1;
    for(int i = 0; i < g[in].size(); i++)
    {
        if(!passed[g[in][i]] && siz[g[in][i]] > tam/2 && !vis[g[in][i]])
        {
            
            if(maxi < siz[g[in][i]])
            {
                imaxi = g[in][i];
                maxi = siz[g[in][i]];
            }
        }
    }
    if(maxi != 0)
        return get_centroid(imaxi, g, siz, vis, tam);
    else {
        passed[in] = 1;
        return in;
    }
}
ll dfs(vector<vl>& g, vector<bool>& vis, ll in)
{
    if(!vis[in]){
        vis[in] = 1;
        siz[in] = 1;
        
        for(int i = 0; i < g[in].size(); i++)
        {   
            if(!passed[g[in][i]] && !vis[g[in][i]])
                siz[in] += dfs(g, vis, g[in][i]);
        }
        return siz[in];
    }
    return 0;
}
ll centroid_decomp(vector<vl>& g, ll deph, ll in, ll p)
{
    vector<bool> vis(g.size(), 0);
    dfs(g, vis, in);
    vis.clear();
    vis.assign(g.size(),0);

    ll cen = get_centroid(in, g, siz, vis, siz[in]);
    depht[cen] = deph;
    parent[cen] = p;

    for(int i = 0; i< g[cen].size(); i++)
    {
        if(!passed[g[cen][i]]){
            ll child = centroid_decomp(g, deph + 1, g[cen][i], cen);
            
            CTree[cen].push_back(child);
        }
    }
    return cen;

}

void update(ll u, ll in, SparseTableLCA& AC)
{
    ans[in] = min(ans[in], AC.Dist(u, in));
    if(parent[in] != -1) update(u, parent[in], AC);
}
ll query(ll u, ll in, SparseTableLCA& AC)
{

    ll mini = ans[in] + AC.Dist(u, in);
    if(parent[in] != -1) mini = min(mini, query(u, parent[in], AC));
    return mini;
}


int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n, m, x, y;
  cin >> n >> m;
  vector<vl>g (n,vl(0));
  for(int i = 0; i < n-1; i++)
  {
      cin >> x >> y;
      x--; y--;
      g[x].push_back(y);
      g[y].push_back(x);
  }
  depht.assign(n,0);
  passed.assign(n,0);
  parent.assign(n,-1);
  siz.assign(n,0);
  CTree.assign(n, vl(0));
  ans.assign(n, INF);
  ll ini = centroid_decomp(g, 0, 0, -1);

    vl vis(n,0);
    vl parentLCA(n,-1);
    D.assign(n,INF);D[ini]=0;
    queue<ll> q;
    q.emplace(ini);
    while(!q.empty()){
        ll k=q.front();q.pop();
        if(!vis[k]){
            vis[k]=true;
            for(ll i=0;i<g[k].size();i++)
            {
                    if(!vis[g[k][i]])
                    {
                        parentLCA[g[k][i]]=k;
                        D[g[k][i]]=D[k]+1;
                        q.push(g[k][i]);
                    }
            }
        }
    }

  SparseTableLCA AC(parentLCA);
  update(0, 0, AC);


  for(int i = 0; i < m; i++)
  {
      cin >> x >> y;
      y--;
      if(x == 1)
      {
          update(y, y, AC);
      }
      else
      {
          cout << query(y, y, AC) << "\n";
      }
      
  }
  
  
}
