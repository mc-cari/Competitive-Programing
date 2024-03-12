#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

#define rep(i, n) for(int i = 0; i < (int)n; i++)



int main() {
  ll n,m,cl,ce,v; cin>>n>>m>>cl>>ce>>v;
  vl L(cl); rep(i, cl) cin>>L[i];
  vl E(ce); rep(i, ce) cin>>E[i];
  int q; cin>>q;
  rep(_, q) {
    ll x1,y1,x2,y2; cin>>y1>>x1>>y2>>x2;
    ll ans = 1e17;
    auto itl = lower_bound(L.begin(), L.end(), x1);
    auto ite = lower_bound(E.begin(), E.end(), x1);
    if(y1 == y2) {
      ans = min(ans, abs(x1 - x2));
    }
    if(L.size()) { 
      if(itl == L.end()) {
        itl = prev(itl);
        ans = min(ans, abs(x1 - *itl) + abs(*itl - x2) + abs(y1 - y2));
      }
      else if(itl == L.begin()) {
        ans = min(ans, abs(x1 - *itl) + abs(*itl - x2) + abs(y1 - y2));
      }
      else {
        ans = min(ans, abs(x1 - *itl) + abs(*itl - x2) + abs(y1 - y2));
        itl = prev(itl);
        ans = min(ans, abs(x1 - *itl) + abs(*itl - x2) + abs(y1 - y2));
      }
    }
    if(E.size()) {
      if(ite == E.end()) {
        ite = prev(ite);
        ans = min(ans, abs(x1 - *ite) + abs(*ite - x2) + (abs(y1 - y2) + v - 1) / v);
      }
      else if(ite == E.begin()) {
        // cout<<"entre aca\n";
        // cout<<abs(x1 - *ite)<<' '<<abs(*ite - x2)<<' '<<(abs(y1 - y2) + v - 1) / v<<'\n';
        ans = min(ans, abs(x1 - *ite) + abs(*ite - x2) + (abs(y1 - y2) + v - 1) / v);
      }
      else {
        ans = min(ans, abs(x1 - *ite) + abs(*ite - x2) + (abs(y1 - y2) + v - 1) / v);
        ite = prev(ite);
        ans = min(ans, abs(x1 - *ite) + abs(*ite - x2) + (abs(y1 - y2) + v - 1) / v);
      }
    }
    cout<<ans<<'\n';
    
  }



  return 0;
}