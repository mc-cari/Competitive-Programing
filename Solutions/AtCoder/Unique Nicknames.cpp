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



int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    ll n;
    cin >> n;
    string s, t;
    vector<string> ss, tt;
    map<string, ll> ds, dt;
    for(int i = 0; i < n; i++)
    {
        cin >> s >> t;
        ss.push_back(s);
        tt.push_back(t);
        ds[s]++;
        if(s != t) ds[t]++;
    }
    bool o = 1;

    for(int i =0; i < n; i++)
    {

        if(ds[ss[i]] > 1 && ds[tt[i]] > 1)
        {
            o = 0;
            break;
        }
    }
    if(o) cout << "Yes\n";
    else cout << "No\n";
    


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}