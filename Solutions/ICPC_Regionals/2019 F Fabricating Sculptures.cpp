#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e9
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://matcomgrader.com/problem/9639/fabricating-sculptures/

ll memo[5001][5001];
ll M = 1e9 + 7;

ll dp(ll b, ll base)
{
    
    if(b < 0 || base <= 0)return 0;

    if(memo[b][base] != -1)return memo[b][base];

    if(b == 0)return 1;

    if(base == 1)return 1;
    
    return memo[b][base] = ((dp(b - base, base) + (2 * dp(b, base - 1))%M)%M - dp(b, base - 2) + 2*M)%M;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(memo, -1, sizeof(memo));
    ll s, b;
    cin >> s >> b; 
    b -= s;

    cout << dp(b, s) << "\n";
   
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
