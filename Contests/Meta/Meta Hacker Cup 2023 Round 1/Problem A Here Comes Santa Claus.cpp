#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef vector<int> vi;
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    repx(T, 1, t+1)
    {
        ll n;
        cin >> n;
        vector<double> c(n);
        rep(i, n)cin >> c[i];
        sort(ALL(c));
        db ans;

        if (n != 5)
        {
            ans = (c[n-1] + c[n-2])/2.0 - (c[0] + c[1])/2.0;
        }
        else{
            ans = (c[n-1] + c[n-3])/2.0 - (c[0] + c[1])/2.0;
            ans = max(ans, (c[n-1] + c[n-2])/2.0 - (c[0] + c[2])/2.0);
        }

        cout << "Case #" << T << ": " << fixed << setprecision(9) << ans << "\n";
    }
    
}