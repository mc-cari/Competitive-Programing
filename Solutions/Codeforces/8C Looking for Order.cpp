#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e17
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/problemset/problem/8/C

vp cds;

ll memo[(1 << 24)], n;
vl res;
ll dist(ll x, ll y)
{
  return (cds[x].first - cds[y].first) * (cds[x].first - cds[y].first) + (cds[x].second - cds[y].second) * (cds[x].second - cds[y].second);
}

ll dp(ll in)
{
  if(in == 0) return memo[in] = 0;
  if(memo[in] != -1) return memo[in];

  ll ans = INF, ind = -1;
  for(ll i = 0; i < n; i++)
    if((in & (1 << i))){
      ind = i;
      break;
    }
  

  ans = min(ans, dp(in - (1 << ind)) + dist(0, ind + 1) * 2);

  ll ind2 = -1;
  for(ll i = ind + 1; i < n; i++)
    if((in & (1 << i))){
      ind2 = i;
      ans = min(ans, dp(in - (1 << ind) - (1 << ind2)) + dist(0, ind + 1) + dist(0, ind2 + 1) + dist(ind + 1, ind2 + 1));
    }
  return memo[in] = ans;
}

void rec(ll in)
{
  if(in == 0) return;
  ll ans = INF, cont = 0, ind = -1, id = -1;
  for(ll i = 0; i < n; i++)
    if((in & (1 << i))){
      ind = i;
      break;
    }
  

  ans = min(ans, dp(in - (1 << ind)) + dist(0, ind + 1) * 2);

  ll ind2 = -1;
  for(ll i = ind + 1; i < n; i++)
    if((in & (1 << i))){
      ind2 = i;
      if(dp(in - (1 << ind) - (1 << ind2)) + dist(0, ind + 1) + dist(0, ind2 + 1) + dist(ind + 1, ind2 + 1) < ans)
      {
        id = i;
        ans = dp(in - (1 << ind) - (1 << ind2)) + dist(0, ind + 1) + dist(0, ind2 + 1) + dist(ind + 1, ind2 + 1);
      }
    }

  if(id == -1)
  {
    res.push_back(ind + 1);
    res.push_back(0);
    rec(in - (1 << ind));
  }
  else
  {
    res.push_back(ind + 1);
    res.push_back(id + 1);
    res.push_back(0);
    rec(in - (1 << ind) - (1 << id));
  }

}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll x, y;
    cin >> x >> y;
    memset(memo, -1, sizeof(memo));
    cds.push_back({x, y});
    cin >> n;
    for(int i = 0; i < n; i++)
    {
      cin >> x >> y;
      cds.push_back({x, y});
    }
    cout << dp((1 << n) - 1) << "\n";
    res.push_back(0);
    rec((1 << n) - 1);
    for(int i = 0; i < res.size(); i++)
    {
      cout << res[i];
      if(i + 1 < res.size())cout << " ";
      else cout << "\n";
    }
    
    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
