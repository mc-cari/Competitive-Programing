#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://www.urionlinejudge.com.br/judge/es/problems/view/2012

ll vis[101][101];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    ll n, m, x;
    while(cin >> n >> m){
      ll c[n][m];
      for(int i = 0; i < n; i++)for(int j = 0; j < m; j++)
      {
        cin >> c[i][j];
      }
      ll ans = 0;
      for(int i = 0; i < n-1; i++)
      {
        bool o = 0;
        if(c[i+1][0] > c[i][0]) o = 1;
        if(c[i+1][0] != c[i][0])ans ++;
        ll l = min(c[i][0], c[i+1][0]), r = max(c[i][0], c[i+1][0]);
        for(int j = 1; j < m; j++)
        {
          if(c[i][j] != c[i+1][j] && c[i][j-1] == c[i+1][j-1]) ans++;
          else if((!o && c[i][j] >= c[i+1][j]) || (o && c[i][j] < c[i+1][j]))
          {
            if((min(c[i+1][j], c[i][j]) >= r || max(c[i+1][j], c[i][j]) <= l) && c[i+1][j] != c[i][j])ans++;

          }
          else if(c[i+1][j] != c[i][j]) ans++;
          o = 0;
          if(c[i+1][j] > c[i][j]) o = 1;
          l = min(c[i+1][j], c[i][j]); r = max(c[i+1][j], c[i][j]);
          
        }

      }
      for(int i = 0; i < m-1; i++)
      {
        bool o = 0;
        if(c[0][i+1] > c[0][i]) o = 1;
        if(c[0][i+1] != c[0][i])ans ++;
        ll l = min(c[0][i], c[0][i+1]), r = max(c[0][i], c[0][i+1]);
        for(int j = 1; j < n; j++)
        {
          if(c[j][i] != c[j][i+1] && c[j-1][i] == c[j-1][i+1]) ans++;
          else if((!o && c[j][i] >= c[j][i+1]) || (o && c[j][i] < c[j][i+1]))
          {

            if((min(c[j][i+1], c[j][i]) >= r || max(c[j][i+1], c[j][i]) <= l) && c[j][i+1] != c[j][i])ans++;

          }
          else if(c[j][i+1] != c[j][i]) ans++;
          o = 0;
          if(c[j][i+1] > c[j][i]) o = 1;
          l = min(c[j][i+1], c[j][i]); r = max(c[j][i+1], c[j][i]);
          
        }

      }

      memset(vis, 0, sizeof(vis));
      for(int i = 0; i < n; i++) for(int j = 0; j < m; j++)
      {
        if(!vis[i][j])
        {
          ans++;
          queue<pll> q;
          q.push({i, j});
          while(!q.empty())
          {
            pll t = q.front();
            q.pop();
            if(!vis[t.first][t.second])
            {
              vis[t.first][t.second] = 1;
              ll x = t.first, y = t.second;
              if(x > 0 && c[x-1][y] == c[x][y] && !vis[x-1][y]) q.push({x-1, y});
              if(x < n-1 && c[x+1][y] == c[x][y] && !vis[x+1][y])q.push({x+1, y});
              if(y > 0 && c[x][y-1] == c[x][y] && !vis[x][y-1])q.push({x, y-1});
              if(y < m-1 && c[x][y+1] == c[x][y] && !vis[x][y+1])q.push({x, y+1});
            }
          }
        }
      }

      cout<<ans + 5<<"\n";
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
