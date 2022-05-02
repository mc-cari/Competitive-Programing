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
        ll n, x;
        cin >> n;
        vl c;
        for(int i = 0; i < n; i++)
        {
            cin >> x;
            c.push_back(x);
            
        }
        sort(ALL(c));
        ll ind = 0;
        for(auto it : c)
        {
            if(it >= ind + 1)
                ind++;
            
        }
        cout << "Case #" << T << ": " << ind << "\n";
    }


    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}