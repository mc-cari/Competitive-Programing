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
        ll n, x, ans = 0, maxi = -1;
        deque<ll> c;
        cin >> n;
        for(int i = 0; i < n; i++)
        {
            cin >> x;
            c.push_back(x);
        }
        while(!c.empty())
        {
           
            if(c.back() < c.front())
            {
                if(c.back() >= maxi) ans++;
                maxi = max(maxi, c.back());
                c.pop_back();
                
            }
            else
            {
                if(c.front() >= maxi) ans++;
                maxi = max(maxi, c.front());
                c.pop_front();
                
            }
            
        }

        cout << "Case #" << T << ": " << ans << "\n";



    }

    return 0;
    
}