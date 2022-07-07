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

//https://codeforces.com/gym/103081/problem/F

ll R, N, M;

ll memo[2040][2040];
// node m to insert | two sons free node count
ll dp(ll m, ll two)
{
    // n nodes placed
    ll n = N - m;
    ll one =  n + 1 + ((m >= R) ? -2*two : -2*(two+1)); // R have two sons but its not counted

    if(one < 0 || two < 0) return 0;
    if(m == 0) return 1%M;

    if(memo[n][two] != -1) return memo[n][two];

    ll ans = 0;
    if(m != R)
    {
        // insert in a node with two sons free
        ans += dp(m-1, two) * two;
        // insert in a node with one son free
        ans += dp(m-1, two+1) * one;
        ans %= M;
    }
    else
    {
        ans += (dp(m-1, two-1) * two + dp(m-1, two) * one) % M;
    }
    
    return memo[n][two] = ans;
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
    cin >> R >> N >> M;
    if(R == N)
    {
        if(N == 1) cout << 1%M << "\n";
        else cout << "0\n";
        
    }
    else
    {
        memset(memo, -1, sizeof memo);
        // Node N already placed
        cout << dp(N-1, 1) << "\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
