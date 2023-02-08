#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

const int M = 1e9+7;
// binary exponent 
ll expmod(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b %M;
        b = b*b %M; e >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0,LLONG_MAX);


    ll n, in = 0;
    cin >> n;
    vl v1(n, 0), v2(n, 0);

    map<ll, ll> m;
    rep(i, n) {
        cin >> v1[i];
        m[v1[i]] = 1;
    }
    rep(i, n) cin >> v2[i];
    for(auto it : m) {
        m[it.first] = in;
        in++;
    }
    rep(i, n){
        v1[i] = m[v1[i]];
        v2[i] = m[v2[i]];
        if(i < n-1) {
            v1.pb(v1[i]);
            v2.pb(v2[i]);
        }
    }

    vl rnd(n, 0);
    rep(i, n) rnd[i] = distribution(generator);
    
    ll ac = 0;
    unordered_map<ll, ll> m2;
    m2[0]++;
    rep(i, n-1) {
        
        ac += rnd[v1[i]] - rnd[v2[i]];
        m2[ac]++;

        
    }
    ll ans = 0;
    for(auto it : m2){
        if(it.second >= 2){
            ans += expmod(2, it.second) - it.second - 1 + M;
            ans %= M;
        }
    }
    cout << ans << "\n";

}