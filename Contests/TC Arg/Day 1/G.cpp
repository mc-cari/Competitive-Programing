#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vl vector<ll> 
#define rep(i, n) for(int i = 0; i<(int)n; ++i)
const int mxN = 1e5 + 2;
vl AccA, AccB, A, B;
int n1, n2;


ll cost(ll m) {
  auto itl = lower_bound(A.begin(), A.end(), m) - A.begin();
  auto itr = lower_bound(B.begin(), B.end(), m) - B.begin();
  ll L = 0, R = 0;
  if(itl == n1) itl--;
  L = -AccA[itl] + (itl + 1) * m;
  R = AccB[itr] - (n2 - itr) * m;
  // cerr<<m<<' '<<itl<<' '<<L<<'\n';
  // cerr<<m<<' '<<itr<<' '<<R<<'\n';
  return R + L;
}

ll cost2(ll m) {
  ll curr = 0;
  rep(i, n1) {
    if(A[i] > m) break;
    curr += m - A[i];
  }
  for(int i = n2 - 1; i >= 0; i--) {
    if(B[i] < m) break;
    curr += B[i] - m;
  }
  return curr;
}



int main() {
  cin>>n1>>n2;
  A.resize(n1); B.resize(n2);
  AccA.resize(n1); AccB.resize(n2);
  rep(i, n1) cin>>A[i];
  rep(i, n2) cin>>B[i];
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  AccA[0] = A[0];
  rep(i, n1 - 1) AccA[i + 1] = AccA[i] + A[i + 1];
  AccB[n2 - 1] = B[n2 - 1];
  for(int i = n2 - 2; i >= 0; i--) AccB[i] = AccB[i + 1] + B[i];
  ll l = 1e10, r = 0;
  rep(i, n1) l = min(l, A[i]);
  rep(i, n2) r = max(r, B[i]);
  if(l >= r) {
    cout<<0<<'\n';
    return 0;
  }
  while(l < r) {
    ll m = (l + r) / 2;
    ll L = cost2(m);
    ll R = cost2(m + 1);
    
    // cout<<m<<' '<<L<<' '<<R<<'\n';
    if(R >= L) r = m;
    else l = m + 1;
  }
  // cout<<l<<' '<<cost(l)<<'\n';
  cout<<cost2(l)<<'\n';
  return 0;
}


