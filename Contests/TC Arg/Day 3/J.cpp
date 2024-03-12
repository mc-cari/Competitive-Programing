#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;

#define rep(i, n) for(int i = 0; i < (int)n; i++)



int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, m, r, k;
  cin >> n >> m >> r >> k;
  

  double n_block = (m - r + 1) * (n - r + 1), ans = 0;

  if(r == 1)
  {
    ans = k;
    cout << fixed << setprecision(10) << ans/n_block << "\n";
    return 0;
  }

  vector<int> dx = {-1, 1, 0, 0}, dy = {0, 0, -1, 1};

  
  priority_queue<tuple<ll, int, int>> q;
  unordered_map<ll, bool> vis;
  ll x = n/2, y = m/2;
  q.push({(-r + (2 + min(m - y - 1, r -1) + min(y, r-1))) * (-r + (2 + min(n - x - 1, r-1) + min(x, r-1))), n/2, m/2});
  
  while(!q.empty() && k)
  {
    ll w;
    int x, y;
    tie(w, x, y) = q.top();
    q.pop();

    if(vis[x*m + y]) continue;
    

    k--;
    vis[x*m + y] = 1;
    ans += w;
    //cout << x << " " << y << " " << w << endl;

    rep(z, 4)
    {
      ll nx = x + dx[z], ny = y + dy[z];
      if(nx < 0 || nx >= n || ny < 0 || ny >= m)continue;

      if(!vis[nx * m + ny])
      {
        ll nw = (-r + (2 + min(m - ny - 1, r -1) + min(ny, r-1))) * (-r + (2 + min(n - nx - 1, r-1) + min(nx, r-1)));
        
        //cout << ( min(m - ny - 1, r -1) )<<" "<<min(ny, r-1)<<endl;
        q.push({nw, nx, ny});
      }
    } 
  }
  cout << fixed << setprecision(10) << ans/n_block << "\n";
}