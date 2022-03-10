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


struct BIT { 

    vl bit;
    BIT(ll n) { bit.assign(n+1, 0); }
   
    ll psq(ll k) {
        ll sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
  
    ll rsq(ll a, ll b) {
        return psq(b) - psq(a-1);
    }

    void add(ll k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }

};


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
        BIT bit(1e5);
        cout << "Case #" << T << ":";
        for(int i = 0; i < n; i++)
        {
            cin >> x;
            bit.add(min((ll)1e5, x), 1);
            ll l = 1,r = 1e5 ,p , res = -1;
            while(l <= r)
            {
                p = (l + r) / 2;
                if(bit.rsq(p, 1e5) >= p)
                {
                    res = p;
                    l = p+1;
                }
                else r = p-1;
            }
            cout << " " << res;
        }
        cout << "\n";
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}