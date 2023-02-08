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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1283

ll w[300][300];
vector<vl> g;
vector<vp> g2;
void dfs(ll s, ll i, ll c)
{
    if(c > w[s][i]) return;
    if(c > g[s][i]) w[s][i] = min(w[s][i], c);

    for(auto it : g2[i])
        dfs(s, it.first, c + it.second);

}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, x, y, W, T = 0;
    while(cin >> n >> m)
    {
        T++;
        cout << "Set #" << T << "\n";
        g.assign(n, vl(n, INF));
        g2.assign(n, vp());
        for(int i = 0; i < n; i++)
        {
            g[i][i] = 0;
            for(int j = 0; j < n; j++)
                w[i][j] = INF;
        }
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y >> W;
            g[x][y] = g[y][x] = W; 
            g2[x].push_back({y, W});
            g2[y].push_back({x, W});

        }
    
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)

                    if(g[i][k] + g[k][j] < g[i][j])
                        g[i][j] = g[i][k] + g[k][j];

        for(int i = 0; i < n; i++) dfs(i, i, 0);
        ll q;
        cin >> q;
        while(q--)
        {
            cin >> x >> y;
            ll mini = INF;
            
            if(w[x][y] == INF) cout << "?\n";
            else cout << w[x][y] << "\n";
        }
    }
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
