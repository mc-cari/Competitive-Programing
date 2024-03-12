#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define ll long long
#define ull unsigned long long
#define vl vector<ll> 
#define rep(i, n) for(int i = 0; i<(int)n; ++i)

const int mxN = 1e5 + 5;
ll ST[4 * mxN];

void update(ll pos, ll x, ll l = 0, ll r = mxN, ll u = 0) {
  if(l == r) ST[u] = x;
  else {
    ll m = (l + r) / 2;
    if(pos <= m) update(pos, x, l, m, 2 * u + 1);
    else update(pos, x, m + 1, r, 2 * u + 2);
    ST[u] = max(ST[2 * u + 1], ST[2 * u + 2]);
  }
}

ll query(ll i, ll j, ll l = 0, ll r = mxN, ll u = 0) {
  if(i > j) return 0;
  if(i <= l and r <= j) return ST[u];
  if(r < i or l > j) return 0;
  ll m = (l + r) / 2;
  return max(query(i, j, l, m, 2 * u + 1), query(i, j, m + 1, r, 2 * u + 2));
}


int main() {
  int n; cin>>n;
  vl D(n), V(n), T(n);
  rep(i, n) cin>>D[i]>>V[i]>>T[i];
  set<ll> S;
  rep(i, n) S.insert(D[i]);
  vl Comp;
  for(auto u: S) Comp.push_back(u);
  ll ans = 0;
  vl Ans(n, 0);
  memset(ST, 0, sizeof(ST));

  rep(i, n) {
    ll l = lower_bound(Comp.begin(), Comp.end(), D[i] - T[i]) - Comp.begin();
    ll r = lower_bound(Comp.begin(), Comp.end(), D[i]) - Comp.begin();
    ll curr = V[i] + query(l, r);
    // cout<<curr - V[i]<<' '<<V[i]<<'\n';
    Ans[r] = max(Ans[r], curr);
    ans = max(ans, Ans[r]);
    update(r, Ans[r]);
  }
  cout<<ans<<'\n';




  return 0;
}

