#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e5
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=241

ll joseph(ll n)
{
    ll m = 0;
    for(int j = 1; j < 10000000; j++){
        vl a(n+1, 0);
        bool o = 1;
        for(int i = 0; i < n/2; i++)
        {
            
            a[i+1] = (a[i] + j-1)%(n-i);
            if(a[i+1] < n/2 )
            {
                o = 0;
                break;
            }
            
        }
        if(o) return j;
    }
    return 0;

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    map<ll,ll> ans;
    for(int i = 1; i < 14; i++)
    {
        ans[i] = joseph(i*2);
    }
    ll t;
    while(cin >> t && t)
    {
        cout<<ans[t]<<"\n";
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

