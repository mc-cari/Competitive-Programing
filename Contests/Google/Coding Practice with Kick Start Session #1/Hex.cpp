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


struct UF{
    vl p, r;
    UF(ll n)
    {
        for(ll i = 0; i < n; i++)
        {
            p.push_back(i);
            r.push_back(0);
        }
    }
    ll find(ll x)
        {return p[x] = p[x] == x ? x : find(p[x]);}
    void join(ll x, ll y)
    {
        x = find(x);
        y = find(y);
        if(x != y)
        {

            if(r[x] >= r[y])
            {
                if(r[x] == r[y]) r[x]++;
                p[y] = x;
            }
            else p[x] = y;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    for(int T = 1; T <= t; T++)
    {
        ll n, rs = 0, bs = 0; 
        cin >> n;

        UF b(n*n + 2), r(n*n + 2);
        char g[n][n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                cin >> g[i][j];
                if(g[i][j] == 'R') rs++;
                else if(g[i][j] == 'B') bs++;
            }
        cout << "Case #" << T << ": ";
        if(abs(rs - bs) > 1)
        {
            cout << "Impossible\n";
            continue;
        }
                
        for(int i = 0; i < n; i++)
        {
            if(g[0][i] == 'R') r.join(i, n*n);
            if(g[n-1][i] == 'R') r.join((n-1)*n + i, n*n + 1);

            if(g[i][0] == 'B') b.join(i*n, n*n + 1);
            if(g[i][n-1] == 'B') b.join(i*n + n-1, n*n);
        }
        
        

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(j < n-1)
                {
                    if(g[i][j] == 'R' && g[i][j+1] == 'R')
                        r.join(i*n + j, i*n + j + 1);

                    else if(g[i][j] == 'B' && g[i][j+1] == 'B')
                        b.join(i*n + j, i*n + j + 1);

                }
                if(i == n-1)continue;

                if(g[i][j] == 'R' && g[i+1][j] == 'R')
                    r.join(i*n + j, i*n + j + n);

                else if(g[i][j] == 'B' && g[i+1][j] == 'B')
                    b.join(i*n + j, i*n + j + n);
                
                if(j > 0)
                {
                    if(g[i][j] == 'R' && g[i+1][j-1] == 'R')
                        r.join(i*n + j, i*n + j + n - 1);

                    else if(g[i][j] == 'B' && g[i+1][j-1] == 'B')
                        b.join(i*n + j, i*n + j + n - 1);
                }

            }
        }
        if(b.find(n*n) == b.find(n*n + 1) && r.find(n*n) == r.find(n*n + 1))
            cout << "Impossible\n";
        else if(b.find(n*n) == b.find(n*n + 1))
            cout << "Blue wins\n";
        else if(r.find(n*n) == r.find(n*n + 1))
            cout << "Red wins\n";
        else cout << "Nobody wins\n";

            
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}