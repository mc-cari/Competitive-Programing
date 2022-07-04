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



db check(ll need, db po)
{
    db ans = 0, mul = log2(need), po2 = 5;

    while(need != 1)
    {
        ans += mul*pow(2, -po/4);
        po -= 2;
        mul /= 2;
        need /=2;

    }
    return ans;
}
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    ll n, x;
    cin >> n;
    vl c;
    ll need = 2;
    db ans = pow(2, -3.0/4);
    
    //cout << pow(2, -5.0/4) + 2*pow(2, -7.0/4) << " " << pow(2, -3.0/4) << " "<<1.60965532263 - pow(2, -3.0/4)<<"\n";

    vl d;
   

    for(int i = 0; i < n-1; i++)
    {
        cin >> x;
        c.push_back(x);

        ll val = min(x, need);
        d.push_back(val);
        need -= val;


        need *= 2;
    }
    for(int i = n-2; i > 0; i--)
    {
        d[i-1] += d[i]/2;
        ans += d[i]/2 * pow(2, -db(i*2 + 3)/4);
    }
    if(need != 0) cout << "impossible\n";
    else cout << fixed << setprecision(10) << ans << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}