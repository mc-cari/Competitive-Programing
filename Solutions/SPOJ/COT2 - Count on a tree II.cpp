#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);
//https://www.spoj.com/problems/COT2/
ll maxlog2(ll x){
    return (63 - __builtin_clzll(x));
}
struct SparseTableLCA
{
    ll maxlg;
    vector<vl >SP;
    vector<vl >MN;
    vl D;
    SparseTableLCA(vector<vl>& g, ll ini)
    {
        ll n = g.size();
        vl vis(n,0), parent(n,-1);
        D.resize(n,INF);D[ini]=0;
        queue<ll> q;
        q.emplace(ini);
        while(!q.empty()){
            ll k=q.front();q.pop();
            if(!vis[k]){
                vis[k]=1;
                for(ll i=0;i<g[k].size();i++)
                {
                        if(!vis[g[k][i]])
                        {
                            parent[g[k][i]]=k;
                            D[g[k][i]]=D[k]+1;
                            q.push(g[k][i]);
                        }
                }
            }
        }

        SP.clear();
        SP.push_back(parent);
        maxlg=maxlog2(n);
        for(ll i=1;i<=maxlog2(n);i++)
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
    {// lleva n a la profundidad a
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
};

ll block;
struct Query 
{ 
    int L, R, id, lca, type; 
}; 

bool compare(Query x, Query y) 
{ 
    // Different blocks, sort by block. 
    if (x.L/block != y.L/block) 
        return x.L/block < y.L/block; 
  
    // Same block, sort by R value 
    return x.R < y.R; 
} 
vl visn;
vl elements;
ll add(vp& a, int id)
{
    ll ret = 0;
    if(visn[a[id].second] > 0)
    {
      if(elements[a[id].first] == 1)ret = -1;
      elements[a[id].first]--;
    }
    else
    {
      if(elements[a[id].first] == 0)
        ret = 1;
      elements[a[id].first]++;
    }
    visn[a[id].second]++;
    return ret;
}
ll remove(vp& a, int id)
{
    ll ret = 0;
    if(visn[a[id].second] > 1)
    {
      if(elements[a[id].first] == 0)ret = 1;
      elements[a[id].first]++;
    }
    else
    {
      if(elements[a[id].first] == 1)
        ret = -1;
      elements[a[id].first]--;
    }
    visn[a[id].second]--;
    return ret;
}
vl w, ind, out, ans;
void queryResults(vp& a, vector<Query>& q) 
{ 

    block = (int)sqrt(a.size()); 
    ans.assign(q.size(),0);

    sort(ALL(q), compare); 
   
    ll currL = 0, currR = 0; 
    ll currans = 0; 
  
    for (int i=0; i<q.size(); i++) 
    { 
        // L and R values of current range 
        int L = q[i].L, R = q[i].R; 
        while (currR <= R) 
        { 
            currans += add(a, currR);
            currR++; 
        }
        while (currL > L) 
        { 
            currans += add(a, currL-1);
            currL--; 
        } 
        while (currR > R+1) 
        { 
            currans += remove(a, currR-1); 
            currR--; 
        } 
        while (currL < L) 
        { 
            currans += remove(a, currL);
            currL++; 
        }
        if(q[i].type == 1 && elements[w[q[i].lca]] == 0) 
            currans ++;
        ans[q[i].id] = currans;
        if(q[i].type == 1 && elements[w[q[i].lca]] == 0) 
            currans --;
    } 
} 
ll cont = -1;
vp d;

void dfs(vector<vl>& g, vl& vis, ll in)
{
    if(!vis[in]){
        vis[in] = 1;
        cont++;
        ind[in] = cont;
        d.push_back({w[in], in});
        for(int i = 0; i < g[in].size(); i++)  
            dfs(g, vis, g[in][i]);
        d.push_back({w[in], in});
        cont++;
        out[in] = cont;
    }
}
int main()
{
  ll n, m, x, y;
  vl c;
  cin >> n >> m;
  vector<vl> g(n, vl(0));
  ind.assign(n, 0); out.assign(n, 0);
  for(int i = 0; i < n; i++)
  {
    cin >> x;
    w.push_back(x);
    c.push_back(x);
  }
  sort(ALL(c));
  UNIQUE(c);
  ll in = 0;
  unordered_map<ll, ll> M;
  for(auto it : c)
  {
    M[it] = in;
    in++;
  }
  for(int i = 0; i < n; i++)
    w[i] = M[w[i]];
  for(int i = 0; i < n-1; i++)
  {
    cin >> x >> y;
    g[x-1].push_back(y-1);
    g[y-1].push_back(x-1);
  }
  vl vis(n, 0);
  dfs(g, vis, 0);
  /*for(int i = 0; i < d.size(); i++)
  {
    cout<<d[i].first<<" "<<d[i].second+1<<"\n";
  }
  return 0;*/
  SparseTableLCA LCA(g, 0);
  
  Query q;
  vector<Query>Q;
  for(int i = 0; i < m; i++)
  {
      cin >> x >> y;
      x--; y--;
      ll lca = LCA.LCA(x, y);
      if(ind[y] < ind[x])swap(x, y);
      
      q.L = out[x]; q.R = ind[y];
      if(lca != x && lca != y){
        q.type = 1;
        q.lca = lca;
        q.L = out[x];
        q.R = ind[y];
      }
      else
      {
        q.type = 0;
        q.L = ind[x];
        q.R = ind[y];
      } 
      q.id = i;
      Q.push_back(q);
  }
  visn.assign(n, 0);
  elements.assign(n, 0);
  queryResults(d, Q);
  
  for(int i = 0; i < ans.size(); i++)
  {
      cout << ans[i] << "\n";
  } 
}
