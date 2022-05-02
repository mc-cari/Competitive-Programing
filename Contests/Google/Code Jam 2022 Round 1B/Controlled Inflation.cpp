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


vl maxi, mini;
ll N, memo[1002][2];
ll dp(ll n, ll op)
{
    if(n == N) return 0;
    if(memo[n][op] != -1) return memo[n][op];
    ll prev = 0;
    if(n != 0)
    {
        if(op) prev = maxi[n-1];
        else prev = mini[n-1];
    }
   

    ll ac0 = abs(prev - mini[n]) + abs(mini[n]-  maxi[n]);
    ll ac1 = abs(prev - maxi[n]) + abs(maxi[n] - mini[n]);
    
    ll r1 = dp(n+1, 0) , r2 = dp(n+1, 1);
    ll ans = min(r1 + ac1, r2 + ac0);

    return memo[n][op] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    
    ll t;
    cin >> t;
    
    for(int T = 1; T <= t; T++)
    {
        ll P, x, ans = 0;
        
        cin >> N >> P;
        vector<vl>g(N, vl());
        maxi.assign(N, -1);
        mini.assign(N, INF);
        
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < P; j++)
            {
                cin >> x;
                g[i].push_back(x);
                maxi[i] = max(maxi[i], x);
                mini[i] = min(mini[i], x);
            }
            
        }

        memset(memo, -1, sizeof (memo));
        ans = dp(0, 0);
        
        cout << "Case #" << T << ": " << ans << "\n";



    }

    return 0;
    
}