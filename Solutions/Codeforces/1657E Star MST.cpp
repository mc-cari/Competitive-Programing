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
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/contest/1657/problem/E

ll M = 998244353;

const ll MAXN = 1e5 + 1;
ll F[MAXN], INV[MAXN], FI[MAXN];
// ...
ll Comb(ll n, ll k){
    if(n < k) return 0;
    return F[n]*FI[k] %M *FI[n-k] %M;
}

ll expmod(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b %M;
        b = b*b %M; e >>= 1;
    }
    return ans;
}

ll memo[251][251];
ll n, k;
ll dp(ll i, ll j)
{
   
    if(i == n -1) return 1;
    if(j == k && i != n - 1)return 0;

    if(memo[i][j] != -1) return memo[i][j];
    

    ll ans = 0;
    for(int a = 0; a <= n - 1 - i; a++)
    {
        ll e = a*(a - 1)/ 2 + a * i;
        
        ans += ((dp(i + a, j+1) * Comb(n - i - 1, a)) % M) *  expmod(k - j, e) % M;
        
        ans %= M;
    }

    return memo[i][j] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    F[0] = 1; for(ll i = 1; i < MAXN; i++) F[i] = F[i-1]*i %M;
    INV[1] = 1; for(ll i = 2; i < MAXN; i++) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
    FI[0] = 1; for(ll i = 1; i < MAXN; i++) FI[i] = FI[i-1]*INV[i] %M;

    
    cin >> n >> k;
    memset(memo, -1, sizeof(memo));

    cout << dp(0, 0) << "\n";
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}
