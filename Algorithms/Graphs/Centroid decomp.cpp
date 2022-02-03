#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e8
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

vl B, ac;
ll N, K;

ll memo[502][10010][3];
ll dp(ll in, ll k, ll level)
{
  if(level == 3 || (level == 1 && k == K))
  {
    if(k == K) return 0;
    else return INF;
  }
  if(in == N) return INF;
  if(memo[in][k][level] != -1) return memo[in][k][level];

  ll ans = INF;
  if(level == 0 || level == 2)
  {
    for(int i = in; i < N; i++)
    {
      ans = min(ans, dp(i+1, k + ac[i+1] - ac[in], level + 1) + i - in + 1);
    }
  }
  else
  {
    for(int i = in; i < N; i++)
    {
      ans = min(ans, dp(i+1, k, level + 1));
    }
  }

  return memo[in][k][level] = ans;

}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  ll t;
  cin >> t;
  for(int T = 1; T <= t; T++) {
    
    memset(memo, -1, sizeof(memo));
    ll x;
    cin >> N >> K;
    B.clear();
    ac.clear();
    ac.push_back(0);
    for(int i = 0; i < N; i++)
    {
      cin >> x;
      B.push_back(x);
      ac.push_back(x);
      ac[i+1] += ac[i];
    }
    ll acum = 0;
    for(int i = 0; i < N; i++)
    {
        acum += B[i];
        if(acum == ac[i+1])cout<<"1\n";
        else cout <<"0\n";
    }

    ll ans = INF;
    for(int i = 0; i < N; i++)
    {
      ans = min(ans, dp(i, 0, 0));
    }
    if(ans >= INF) ans = -1;
    cout << "Case #" << T << ": ";
    cout << ans << "\n";
  }




  
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}