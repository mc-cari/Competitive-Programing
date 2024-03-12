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


int main() {
  int t; cin>>t;
  while(t--) {
    ll m, n, k; cin>>m>>n>>k;
    vl A(m); rep(i, m) cin>>A[i];
    ll suma = 0;
    rep(i, m) suma += A[i];
    pll rango = {1e10, 1e10};
    if(suma < 0) {
      rep(i, m) A[i] = -A[i];
      k = -k;
      suma = -suma;
    }
    
    set<pair<ll, ll>> S;
    ll ans = 1e10;
    ll curr = 0;
    S.insert({0, 0});
    rep(i, min(2 * m, n)) {
      curr += A[i % m];
      auto it = S.lower_bound({-k + curr, -m});
      if(it != S.end() and (*it).first == -k + curr) {
        // ans = min(ans, i - (*it).second);
        // cout<<it->ss<<'\n';
        if(ans == i + it->ss + 1 and rango.ff > -it->ss) {
          rango = {-it->ss, i};
        }
        if(ans > i + it->ss + 1) {
          ans = i + it->ss + 1;
          rango = {-it->ss, i};
        }
      }
      S.insert({curr, -i - 1});
    }
    if(2 * m >= n or suma == 0) {
      if(ans == 1e10) cout<<"-1\n";
      else cout<<rango.ff<<' '<<rango.ss<<'\n';
      continue;
    }
    vector<ll> pref(m), suf(m);
    pref[0] = A[0];
    suf[m - 1] = A[m - 1];
    
    rep(i, m - 1) {
      pref[i + 1] = pref[i] + A[i + 1];
      suf[m - i - 2] = suf[m - i - 1] + A[m - i - 2]; 
    }

    map<ll, vector<pll>> mp;
    // multiplo muy grande de suma
    ll inf = (1e16 / suma) * suma;
    rep(i, m) {
      ll aux = (pref[i]%suma + suma) % suma;
      if(!mp.count(aux)) mp[aux] = vector<pll>();
      mp[aux].pb({-pref[i], i});
    }
    for(auto&[u, v] : mp) {
      sort(v.begin(), v.end());
    }

    // USING JUST PREFIX
    if(mp.count((k%suma + suma) % suma)) {
      auto &vec = mp[(k%suma + suma) % suma];
      auto it = lower_bound(vec.begin(), vec.end(), pll(-k, 0));
      if(it != vec.end() and k + it->ff >= 0) {
        ll x = (k + (it->ff)) / suma;
        if(m * x + it->ss + 1 <= n) {
          if(ans == m * x + it->ss + 1) {
            rango = {0, m * x + it->ss};
          }
          if(ans > m * x + it->ss + 1) {
            // cout<<"entre aca1\n";
            ans = m * x + it->ss + 1;
            rango = {0, m * x + it->ss};
          }
        }
      }
    }

    rep(i, m) {
      // USIGN JUST SUFFIX
      if((k - suf[i]) % suma == 0 and k - suf[i] >= 0) {
        ll x = (k - suf[i]) / suma;
        if(m * (x + 1) <= n and ans == m * x + m - i and rango.ff > i) {
          ans = min(ans, m * x + (m - i));
          // cout<<"entre xd\n";
          rango = {i, m * (x + 1) - 1};
        }
        if(m * (x + 1) <= n and ans > m * x + m - i) {
          ans = min(ans, m * x + (m - i));
          // cout<<"entre xd\n";
          rango = {i, m * (x + 1) - 1};
        }
      }
      // USSING PREFIX AND SUFFIX
      if(!mp.count(((k - suf[i])%suma + suma)%suma)) continue;
      auto &vec = mp[((k - suf[i])%suma + suma) % suma];
      auto it = lower_bound(vec.begin(), vec.end(), pll(suf[i]-k, 0));
      if(it == vec.end()) continue;
      if(k - suf[i] + it->ff >= 0) {
        ll x = (k -suf[i] + (it->ff)) / suma;
        if(m * (x + 1) + it->ss + 1 <= n and ans == m * x + (m - i) + it->ss + 1 and rango.ff > i)  {
          // cout<<"entre aca con "<<i<<'\n';
          ans = min(ans, m * x + (m - i) + it->ss + 1);
          rango = {i, m * (x + 1) + it->ss};
        }
        if(m * (x + 1) + it->ss + 1 <= n and ans > m * x + (m - i) + it->ss + 1)  {
          // cout<<"entre aca con "<<i<<'\n';
          ans = min(ans, m * x + (m - i) + it->ss + 1);
          rango = {i, m * (x + 1) + it->ss};
        }
      }
    }

    if(k % suma == 0 and k > 0 and m * (k / suma) <= n and ans > m * (k / suma)) {
      // cout<<"troleao\n";
      ans = min(ans, m * (k / suma));
      rango = {0, m * (k / suma) - 1};
    }
    if(ans == 1e10) cout<<"-1\n";
    else cout<<rango.ff<<' '<<rango.ss<<'\n';
  }
  return 0;
}