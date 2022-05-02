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



    int t;
    cin >> t;
    for(int T = 1; T <= t; T++) {
        string s;
        cin >> s;
        string s2 = "";
        ll cont = 0;
        for(int i = 0; i < s.size()-1; i++)
        {
            cont++;

            if(s[i] < s[i+1])
            {
                cont *= 2;
                while(cont--) s2 += s[i];
                cont++;
            }
            else if(s[i] > s[i+1])
            {
                while(cont--) s2 += s[i];
                cont++;
            }
        }
        cont++;
        while(cont--) s2 += s.back();
        cout << "Case #" << T << ": " << s2 << "\n";
    }

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}