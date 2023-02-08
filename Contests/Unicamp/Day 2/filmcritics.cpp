#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
typedef vector<pll> vp;
typedef double db;

#define INF 1e8
#define EPS 1e-7 
#define ALL(x) x.begin(), x.end()
#define ALLR(x) x.rbegin(), x.rend()
#define pb push_back
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define repx(i, a, b) for(int i = (int)a; i < (int)b; i++)



int main() {
  ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

  ll n, m, k;
  cin >> n >> m >> k;

  if(k % m != 0)
  {
    cout << "impossible\n";
    return 0;
  }
  ll p = k / m, avg = 0;

  pll a[n];
  rep(i, n) {
    ll x;
    cin >> x;
    a[i] = {x, i+1};
  }
  sort(a, a + n);

  vp low, high;

  vl ans;
  rep(i, n)
  {
    if(n - p >= i+1) low.pb(a[i]);
    else high.pb(a[i]);
  }
  reverse(ALL(high));

  bool o = 0;
  rep(i, n)
  {
    
    if(!high.empty() && high.back().first * i >= avg){
      avg += m;
      ans.pb(high.back().second);
      high.pop_back();	
    }
    else if(!low.empty() && low.back().first * i < avg){
      
      ans.pb(low.back().second);
      low.pop_back();
    }
    else{
      cout << "impossible\n";
      return 0;
    }
  }

  rep(i, n) cout << ans[i] << " ";
  cout << "\n";

  return 0;
}