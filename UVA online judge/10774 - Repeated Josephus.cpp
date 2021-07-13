#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
using namespace std;

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1715

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



int joseph(ll n)
{
    ll bit = 60;
    while(!(n & (1LL << bit)))
    {
        bit--;
    }

    n &= ~(1 << bit);
    return 1 + n*2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;

    ll cas = 1;
    while(t--)
    {
        ll n;
        cin >> n;
        ll num = 0, res = -1;
        while(1)
        {
            res = joseph(n);
            num++;
            if(res == n)break;
            n = res;
            
        }
        num--;
        cout<<"Case "<<cas<<": "<<num<<" "<<res<<"\n";
        cas++;
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

