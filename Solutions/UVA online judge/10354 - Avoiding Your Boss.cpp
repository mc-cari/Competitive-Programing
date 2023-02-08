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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1295

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll P, R, BH, OF, YH, M;
    while(cin >> P >> R >> BH >> OF >> YH >> M) 
    {
        BH--; OF--; YH--; M--;
        vector<vl > g(P, vl(P, INF)), g2(P, vl(P, INF));
        for(int i = 0; i < P; i++)
        {
            g[i][i] = 0;
            g2[i][i] = 0;
        }
        vp ed;

        for(int i = 0; i < R; i++)
        {
            ll x, y, w;
            cin >> x >> y >> w;
            x--; y--;
            g[x][y] = g2[x][y] = g[y][x] = g2[y][x]= w;
            ed.push_back({x, y});

        }

        for(int k = 0; k < P; k++)
            for(int i = 0; i < P; i++)
                for(int j = 0; j < P; j++)

                    if(g[i][k] + g[k][j] < g[i][j])
                        g[i][j] = g[i][k] + g[k][j];

        for(auto it : ed)
        {
            ll x, y;
            tie(x, y) = it;
            if(g[BH][x] + g[x][y] + g[y][OF] == g[BH][OF])
            {
                g2[x][y] = INF;
                g2[y][x] = INF;
            }
               
        }
        vl vis(P, 0);
        for(int i = 0; i < P; i++)
            if(g[BH][i] + g[i][OF] == g[BH][OF])
                vis[i] = 1;

        for(int k = 0; k < P; k++)
        {
            if(vis[k])continue;
            for(int i = 0; i < P; i++)
            {
                if(vis[i])continue;
                for(int j = 0; j < P ; j++)

                    if(g2[i][k] + g2[k][j] < g2[i][j] && !vis[j])
                        g2[i][j] = g2[i][k] + g2[k][j];
            }
        }
        if(g2[YH][M] == INF || vis[M] || vis[YH])
            cout << "MISSION IMPOSSIBLE.\n";
        else
            cout << g2[YH][M] << "\n";
    }


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
