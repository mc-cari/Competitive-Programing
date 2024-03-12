#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
#define ff first
#define ss second
#define pb push_back

#define rep(i, n) for(int i = 0; i < (int)n; i++)

const int mxN = 23;
int dp[mxN], f[mxN], n, m;


int main() {
  cin >> n >> m;
  rep(i, n){
    f[i] = (1<<i);
  }
  rep(i, m){
    int a, b;
    cin >> a >> b, --a, --b;
    f[a] |= (1<<b);
    f[b] |= (1<<a);
  }
  if(n == 1 || m == n*(n-1)/2){
    cout << "0";
    return 0;
  }
  int ans = (1<<30)-1;
  for(int mask = 1; mask < (1<<n); ++mask){
    if(__builtin_popcount(mask) > __builtin_popcount(ans)) continue;
    /*
    rep(i, n){
      if(mask & (1<<i)){
        dp[mask] |= f[i];
      }
    }
    */
    int maskcopy = mask;
    while(maskcopy){
      int id = 31-__builtin_clz(maskcopy);
      dp[mask] |= f[id];
      maskcopy ^= (1<<id);
    }
    if(dp[mask] == (1<<n)-1 && __builtin_popcount(ans) > __builtin_popcount(mask)){
      ans = mask;
    }
  }
  cout << __builtin_popcount(ans) << "\n";
  while(ans){
    int id = 31-__builtin_clz(ans);
    cout << id+1 << " ";
    ans ^= (1<<id);
  }
}