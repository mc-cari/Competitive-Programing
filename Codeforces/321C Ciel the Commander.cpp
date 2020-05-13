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

//https://codeforces.com/problemset/problem/321/C

vl siz;
vector<bool> passed;
vl depht;

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
void centroid_decomp(vector<vl>&g, ll deph, ll in)
{

    vector<bool> vis(g.size(), 0);
    dfs(g, vis, in);
    vis.clear();
    vis.assign(g.size(),0);

    ll cen = get_centroid(in, g, siz, vis, siz[in]);
    depht[cen] = deph;

    for(int i = 0; i< g[cen].size(); i++)
    {
        if(!passed[g[cen][i]])
            centroid_decomp(g, deph + 1, g[cen][i]);
    }

}


int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n, x, y;
  cin>>n;
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
  siz.assign(n,0);
  centroid_decomp(g, 0, 0);
  for(int i = 0; i < n; i++)
  {
      cout<<char(depht[i] + 'A');
      i < n-1 ? cout << " " : cout << "\n";
  }
  
}
