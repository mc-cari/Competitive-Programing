#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://open.kattis.com/problems/isomorphicinversion

#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef unsigned long long int ull;
const int MAXLEN = 1e6;

// -----------------------------
// Rolling Hashing: single hash

struct RH_single { // rolling hashing
    static const ull B = 131; // base
    static const ull P = 1e9 + 21; // prime
    static ull pow[MAXLEN];    
    static ull add(ull x, ull y) { return (x + y) % P; }
    static ull mul(ull x, ull y) { return (x * y) % P; }
    static void init() {
        pow[0] = 1;
        rep(i, 1, MAXLEN-1) pow[i] = mul(B, pow[i-1]);
    }    
    vector<ull> h;
    int len;
    void init(vector<int>& s) {
        for (int x : s) assert (x >= 1); // DEBUGGING
        len = s.size();
        h.resize(len);
        h[0] = s[0];
        rep(i,1,len-1) h[i] = add(mul(h[i-1], B), s[i]);
    }
    RH_single(vector<int>& s) { init(s); } // from vector<int>
    RH_single(string& s, char ref) { // from string
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




int main()
{
    RH_single::init();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    ll n = s.size(), ans = 0, prev = 0;
    RH_single R(s, '0');
    bool pending;
    for(int i = 0; i < n/2; i++)
    {
      pending = 1;
      if(R.hash(prev, i) == R.hash(n - i - 1, n - prev - 1))
      {
        ans += 2;
        pending = 0;
        prev = i+1;
      }
      //cout<<i<<" "<<prev<<" "<<ans<<"\n";
    }
    if(pending || n%2 == 1)ans++;

    cout<<ans<<"\n";

}
