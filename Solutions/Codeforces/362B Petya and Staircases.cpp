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

    
    cin >> n >> m;
    vl c;
    set<ll> f;
    for(int i = 0; i < m; i++)
    {
        cin >> x;
        c.push_back(x);
    }
    if(m == 0)
    {
        cout << "YES\n";
        return 0;
    }
    sort(ALL(c));
    if(c[0] == 1 || c.back() == n)
    {
        cout<< "NO\n";
        return 0;
    }
    bool o = 1;
    for(int i = 2; i < m; i++)
    {
        if(c[i] == c[i-1] + 1 && c[i-1] == c[i-2] + 1)o = 0;
    }
    if(o) cout << "YES\n";
    else cout << "NO\n";



    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}