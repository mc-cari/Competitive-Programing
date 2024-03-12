#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, n) for(int i = 0; i<(int)n; ++i)

const int mxN = 2e5+5;

int main(){
  int n;
  cin >> n;
  set<ll> hated;
  set<ll> ans, ans2;
  map<ll, int> mp;
  int cnt = 0, cnt2 = 0;
  rep(_, n){
    int qt, m;
    cin >> qt >> m;
    if(qt == 1){
      cnt++;
      rep(i, m){
        ll x;
        cin >> x;
        mp[x]++;
      }
    }else{
      cnt2++;
      rep(i, m){
        ll x;
        cin >> x;
        hated.insert(x);
      }
    }
  }
  if(cnt2 == n){
    cout << (ll)1e18 - (ll)hated.size();
    return 0;
  }
  for(auto [x, y] : mp){
    if(y == cnt){
      ans.insert(x);
      ans2.insert(x);
    }
  }
  for(auto val : hated){
    if(ans.find(val) != ans.end()){
      ans2.erase(val);
    }
  }
  cout << ans2.size();
}