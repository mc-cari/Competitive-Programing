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
    unordered_map<char, int > m;
    m['a'] = 1;
    m['e'] = 1;
    m['i'] = 1;
    m['o'] = 1;
    m['u'] = 1;
    m['A'] = 1;
    m['E'] = 1;
    m['I'] = 1;
    m['O'] = 1;
    m['U'] = 1;
    m['Y'] = 2;
    m['y'] = 2;
    ll t;
    cin >> t;
    for(int T = 1; T <= t; T++)
    {
        string s;
        cin >> s;
        cout << "Case #" << T << ": " << s << " is ruled by ";
        if(m[s[s.size() - 1]] == 1) cout << "Alice.\n";
        else if(m[s[s.size() - 1]] == 2) cout << "nobody.\n";
        else cout << "Bob.\n";
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}