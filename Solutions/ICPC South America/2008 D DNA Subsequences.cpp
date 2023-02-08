#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e18
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef unsigned long long int ull;
const int MAXLEN = 1e4;



struct RH_single { // rolling hashing
    static const ull B = 131; // base
    static const ull P = 1e9 + 21; // prime
    static ull pow[MAXLEN];    
    static ull add(ull x, ull y) { return (x + y) % P; }
    static ull mul(ull x, ull y) { return (x * y) % P; }
    static void init() {
        pow[0] = 1;
        rep(i,1,MAXLEN) pow[i] = mul(B, pow[i-1]);
    }    
    vector<ull> h;
    int len;
    void init(vector<int>& s) {
        for (int x : s) assert (x >= 1); // DEBUGGING
        len = s.size();
        h.resize(len);
        h[0] = s[0];
        rep(i,1,len) h[i] = add(mul(h[i-1], B), s[i]);
    }
    RH_single(vector<int>& s) { init(s); } // from vector<int>
    RH_single(string& s, char ref = 'a') { // from string
        vector<int> tmp; for(char c : s) tmp.push_back(c - ref + 1);
        init(tmp);
    }
    ull hash(int i, int j) {
        if (i == 0) return h[j];
        return add(h[j], P - mul(h[i-1], pow[j - i + 1]));
    }
    ull hash() { return h[len-1]; }
};
ull RH_single::pow[MAXLEN]; // necessary for the code to compile

ll m, n, k;
string a = "a", b = "a";
ll memo[1001][1001][2];
RH_single h1(a), h2(b);

ll dp(ll i, ll j, ll o)
{
  
  if(i >= n || j >= m) return 0;
  if(memo[i][j][o] != -1) return memo[i][j][o];


  ll ans = max(dp(i+1, j, 0), dp(i, j+1, 0) );
  if(i + k <= n && j + k <= m &&h1.hash(i, i+k-1) == h2.hash(j, j + k-1))ans = max(ans, dp(i+k, j+k, 1) + k);
  if(o && a[i] == b[j]) ans = max(ans, dp(i+1, j+1, 1) + 1);

  return memo[i][j][o] = ans;
}


int main() {
    RH_single::init();
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   

    while(cin >> k && k)
    {
      memset(memo, -1, sizeof(memo));
      cin >> a >> b;
      n = a.size(); m = b.size();
      h1 = RH_single (a);
      h2 = RH_single (b);

      cout << dp(0, 0, 0) << "\n";
    }
    
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
