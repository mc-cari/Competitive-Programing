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

    
    ll t;
    cin >> t;
    
    for(int T = 1; T <= t; T++)
    {
        cout << flush << "00000000\n";
        ll N;
        cin >> N;
        while(N != 0)
        {
            string s = string(N, '1');
            if(8 - N > 0) s += string(8 - N, '0');
            random_shuffle(ALL(s));
            cout << flush << s << "\n";
            cin >> N;
            if(N == -1) break;
        }




    }

    return 0;
    
}