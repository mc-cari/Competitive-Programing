#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }

//https://www.urionlinejudge.com.br/judge/es/problems/view/1298

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n;
    while(cin >> n)
    {
      vector<string>d;
      string s;
      for(int i = 0; i < 2*n-1; i++)
      {
        cin >> s;
        d.push_back(s);
      }
      vector<vl> vis(2*n, vl(2*n+1, 0));
      set<pll>p;
      vector<vector<vl > > block(2*n, vector<vl>(2*n+1, vl(4, 0)));
      for(int i = 0; i < 2*n-1; i++)
      {
        for(int j = 0; j < d[i].size(); j++)
        {
          if(i%2 == 0)
          {
            if(d[i][j] == 'V')
            {
              block[i][2*j][0] = 1;
              block[i][2*j + 1][2] = 1;
              block[i+1][2*j][0] = 1;
              block[i+1][2*j + 1][2] = 1;
            }
            else
            {
              block[i][2*j][1] = 1;
              block[i+1][2*j][3] = 1;
              block[i][2*j+1][1] = 1;
              block[i+1][2*j+1][3] = 1;
            }
            
          }
          else
          {
            if(d[i][j] == 'V')
            {
              block[i][2*j + 1][0] = 1;
              block[i][2*j + 2][2] = 1;
              block[i+1][2*j + 1][0] = 1;
              block[i+1][2*j + 2][2] = 1;
            }
            else
            {
              block[i][2*j + 1][1] = 1;
              block[i+1][2*j + 1][3] = 1;
              block[i][2*j+2][1] = 1;
              block[i+1][2*j+2][3] = 1;
            }
          }
          
        }
      }
      ll cont = 0;
      for(int i = 0; i < 2*n; i++)for(int j = 0; j < 2*n+1; j++)
      { 
        if(!vis[i][j])
        {
          cont++;
          queue<pll> q;
          q.push({i, j});
          while(!q.empty())
          {
            ll I, J;
            tie(I, J) = q.front();
            q.pop(); 
            vis[I][J] = 1;
            if(I > 0 && ! vis[I-1][J])
            {
              if(!block[I][J][3])
                q.push({I-1, J});
              
            }
            if(I < 2*n-1 && ! vis[I+1][J])
            { 
              if(!block[I][J][1])
                q.push({I+1, J});
            }

            if(J > 0 && ! vis[I][J-1])
            {
              if(!block[I][J][2])
                q.push({I, J-1});

            }
            if(J < 2*n && ! vis[I][J+1])
            {
              if(!block[I][J][0])
                q.push({I, J+1});
            }
          }
        }
      }

      cout<<cont-1<<"\n";
    }
      
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
