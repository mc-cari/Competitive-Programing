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
        ll R, C;
        cin >> R  >> C;
        R *= 2;
        C *= 2;
        R++;
        C++;
        vector<string>G(R, string(C, '.'));
        for(int i = 1; i < R; i+= 2)
        {
            for(int j = 1; j < C; j+= 2)
            {
                G[i-1][j-1] = '+';
                G[i-1][j] = '-';
                G[i][j-1] = '|';
                G[i+1][j] = '-';
                G[i][j+1] = '|';
                G[i+1][j+1] = '+';
                G[i-1][j+1] = '+';
                G[i+1][j-1] = '+';

            }
        }
        cout << "Case #" << T << ":" << "\n";
        G[0][0] = '.';
        G[0][1] = '.';
        G[1][0] = '.';
        for(int i = 0; i < R; i++)
        {
            for(int j = 0; j < C; j++)
            {
                cout << G[i][j];

            }cout << "\n";
        }
    }


    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}