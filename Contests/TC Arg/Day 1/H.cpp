#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for(int i = 0; i<(int)n; i++)

const int mxN = 2e5+5;

int main(){
  ll P[26][26][27];
  rep(i, 26) rep(j, 26) cin>>P[i][j][0];
  string s; cin>>s;

  rep(i, 26) P[i][i][0] = 0;
  rep(t, 26) {
    rep(i, 26) {
      rep(j, 26) {
        P[i][j][t + 1] = 1e17;
        rep(k, 26) P[i][j][t + 1] = min(P[i][j][t + 1], P[i][k][t] + P[k][j][0]);
      }
    }
  }
  ll Ans[26][26];
  rep(i, 26) {
    rep(j, 26) {
      Ans[i][j] = 1e17;
      rep(n1, 27) {
        rep(n2, 27) {
          rep(k, 26) Ans[i][j] = min(Ans[i][j], P[i][k][n1] + P[j][k][n2]);
        }
      }
    }
  }
  ll ans = 0;
  int n = s.length();
  rep(i, n / 2) {
    ans += Ans[s[i] - 'a'][s[n - i - 1] - 'a'];
  }
  cout<<ans<<'\n';


  return 0;
}