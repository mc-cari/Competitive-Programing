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


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    for(int T = 1; T <= t; T++)
    {
        ll x;
        vl c1, c2, c3, c4;
        for(int i = 0; i < 4; i++){
            cin >> x;
            c1.push_back(x);
        }
        for(int i = 0; i < 4; i++){
            cin >> x;
            c2.push_back(x);
        }
        for(int i = 0; i < 4; i++){
            cin >> x;
            c3.push_back(x);
        }ll sum = 0;
        for(int i = 0; i < 4; i++){
            c4.push_back(min(c1[i], min(c2[i], c3[i])));
            sum += c4[i];
        }
        cout << "Case #" << T << ": ";
        if(sum < 1e6) cout << "IMPOSSIBLE\n";
        else
        {
            ll res = sum - 1e6;
            for(int i = 3; i >= 0; i--)
            {
                ll aux = min(res, c4[i]);
                res -= aux;
                c4[i] -= aux;
            }
            for(int i = 0; i < 4; i++){
                cout << c4[i];
                if(i < 3) cout << " ";
                else cout << "\n";
            }
        }
        
    }


    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}