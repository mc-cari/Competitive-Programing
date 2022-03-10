#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://codeforces.com/contest/1325/problem/F

vl depht, v, mark, nodes;
vector <vl>g;
bool o = 0;
ll sq = 0;
void dfs(int t)
{
    
    if(!v[t]){
        nodes.push_back(t);
        v[t]=1;
        for(ll i=0;i<g[t].size();i++){

            if(!v[g[t][i]])
            {
              depht[g[t][i]]=depht[t]+1;
              dfs(g[t][i]);
            }
            else if(depht[g[t][i]] != -1 && depht[g[t][i]] < depht[t])
            {   
              if(depht[t] - depht[g[t][i]] + 1 >= sq && !o)
              {
                cout<<"2\n";
                cout<<depht[t] - depht[g[t][i]] + 1<<"\n";
                for(int j = depht[g[t][i]]; j <= depht[t]; j++)
                {
                  cout<<nodes[j]+1<<" ";
                }cout<<"\n";
                o=1;
              }
              
            }
        }
        if(!mark[t])
        {
          for(ll i=0;i<g[t].size();i++){
            mark[g[t][i]]=1;
          }
        }
        nodes.pop_back();
    }
}
    

int32_t main() {
  
  int n, m;
  cin >> n >> m;
  while(sq*sq < n)sq++;
  g.assign(n, vl(0));
  int x, y;
  for(int i = 0; i < m; i++)
  {
    cin >> x >> y;
    x--;y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  depht.assign(n, -1);
  v.assign(n, 0);
  mark.assign(n, 0);
  depht[0] = 0;
  dfs(0);
  if(!o)
  {
    cout<<"1\n";
    for(int i = 0; i<n&&sq; i++)
    {
      if(!mark[i])
      {
        sq--;
        cout<<i+1<<" ";
      }
    }
  }


  return 0;
}
