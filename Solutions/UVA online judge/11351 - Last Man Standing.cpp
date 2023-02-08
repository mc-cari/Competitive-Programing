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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2326

ll joseph(ll n,ll m)
{
    ll Result=0;
    for(int i=1;i<=n;i++)
    {
        Result=(Result+m-1)%i+1;
    }
    return(Result);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t, cas = 1;
    cin >> t;
    while(t--)
    {
        ll n, k;
        cin >> n >> k;
        cout<<"Case "<<cas<<": "<<joseph(n, k)<<"\n";
        cas++;
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

