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

//https://www.hackerrank.com/challenges/johnland/problem

struct UF{
    vl p,r;
    int conjuntos=0;
    UF(int n)
    {
        conjuntos = n;
        for(int i=0;i<n;i++)
        {
            p.push_back(i);
            r.push_back(0);
        }
    }
    int find(int x)
    {
        return p[x] = p[x] == x ? x : find(p[x]);
    }
    void join(int x,int y)
    {
        x=find(x);
        y=find(y);
        if(x!=y)
        {
            conjuntos--;
            if(r[x]>=r[y])
            {
                if(r[x]==r[y]) r[x]++;
                p[y]=x;
            }
            else p[x]=y;
        }
    }
};
vl siz;
ll dfs(vector<vp>& g, vl& vis, ll in)
{
    if(!vis[in]){
        vis[in] = 1;
        siz[in] = 1;
        
        for(int i = 0; i < (ll)g[in].size(); i++)
        {   
            siz[in] += dfs(g, vis, g[in][i].second);
        }
        return siz[in];
    }
    return 0;
}
vl ans(5*1e5, 0);
ll n;
void dfs2(vector<vp>& g, vl& vis, ll in)
{
    if(!vis[in]){
        vis[in] = 1;
        
        for(int i = 0; i < (ll)g[in].size(); i++)
        {   
            if(vis[g[in][i].second])continue;
            if(siz[g[in][i].second] > siz[in])
                ans[g[in][i].first] += siz[in] * (n - siz[in]);
            else
                ans[g[in][i].first] += siz[g[in][i].second] * (n - siz[g[in][i].second]);
            dfs2(g, vis, g[in][i].second);
        }
    }
    return;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll m, x, y, w;
  cin >> n >> m;
  siz.assign(n, 0);
  vector<vp> g(n, vp(0));
  vector<tuple<ll, ll, ll> > t;
  for(int i = 0; i < m; i++)
  {
      cin >> x >> y >> w;
      t.push_back(make_tuple(w, x-1, y-1));
  }
  sort(ALL(t));
  UF uf(n);
  for(int i = 0; i < m; i++)
  {
      tie(w, x, y) = t[i];
      if(uf.find(x) != uf.find(y))
      {
          uf.join(x, y);
          g[x].push_back({w, y});
          g[y].push_back({w, x});
      }
  }
  vl vis(n, 0);
  dfs(g, vis, 0);
  vis.assign(n, 0);
  dfs2(g, vis, 0);
  ll carry = 0;
  for(int i = 0; i < (ll)ans.size(); i++)
  {
      ans[i] += carry;
      carry = ans[i] / 2;
      ans[i] = ans[i] % 2;
  }
  bool o = 0;
  for(int i = (ll)ans.size()-1; i>= 0; i--)
  {
      if(ans[i] == 1)o = 1;
      if(o)cout<<ans[i];
  }
  if(!o)cout<<"0";
  cout<<"\n";
  
  
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
