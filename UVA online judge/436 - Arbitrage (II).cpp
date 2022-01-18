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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=377

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, T = 0;
    while (cin >> n && n)
    {
        T++;
        string s1, s2;
        unordered_map<string, ll> mp;
        for(int i = 0; i < n; i++)
        {
            cin >> s1;
            mp[s1] = i;
        }

        vector<vector<db> > g(n, vector<db>(n, 0));
        for(int i = 0; i < n; i++)
        {
            g[i][i] = 1;
        }

        cin >> m;
        for(int i = 0; i < m; i++)
        {
            db x;
            cin >> s1 >> x >> s2;
            g[mp[s1]][mp[s2]] = x;
        }

        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    //g[i][j] |= (g[i][k] & g[k][j]); to find i is connected with j
                    // if at the end g[i][j] & g[j][i], i and j are in the same SCC

                    // To find minimal max edge in path from i to j
                    //g[i][j] = min(g[i][j], max(g[i][k], g[k][j])); 

                    if(g[i][k] * g[k][j] > g[i][j])
                    {
                        g[i][j] = g[i][k] * g[k][j];
                        
                    }
        bool ans = 0;
        for(int i = 0; i < n; i++)
        {
            if(g[i][i] > 1 + EPS) ans = 1;
            //cout << g[i][i] << "\n";
        }
        cout << "Case " << T << ": ";
        if(ans) cout << "Yes\n";
        else cout << "No\n";
    }
    

    
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
