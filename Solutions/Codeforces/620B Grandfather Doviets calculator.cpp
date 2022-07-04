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

ll n, m, x;

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

    vl c = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    cin >> n >> m;
    ll ans = 0;
    for(int i = n; i <= m; i++)
    {
        string s = to_string(i);
        for(auto it : s) ans += c[it - '0'];
        
    }
    cout << ans << "\n";



    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}