#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e8
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/gym/103185/problem/G

ll N;
db memo[101][101][101];
db dp(ll A, ll B, ll G)
{
    if(A < 0  || B < 0) return 0;
    if(A == 0 && B == 0) return 0;
    if(memo[A][B][G] != -1) return memo[A][B][G];

    db ans = 0;

    if(B > 0)
    ans += (db)B / db(A + B) * dp(A, B-1, G+1);

    if(G && A > 0)
    {
        ans += (db)A / db(A + B) * dp(A - 1, B, G-1);
    }
    else if(A > 0) ans += (db)A / db(A + B) * (dp(A - 1, B, G) +  A);

    return memo[A][B][G] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(memo, -1, sizeof(memo));
    cin >> N;

    cout << fixed << setprecision(10) << dp(N, N, 0) << "\n";
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
