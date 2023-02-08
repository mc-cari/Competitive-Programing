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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1928
int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll N, n, W, T = 0;
    cin >> N;
    while(N--)
    {
        T++;
        cout << "Case #" << T << ":\n";
        cin >> n;
        vector<vl> g(n, vl(n, INF)), adj(n, vl(n, 1));
        
        for(int i = 0; i < n; i++)
            g[i][i] = INF;
        for(int i = 1; i < n; i++)
        {
            for(int j = 0; j < i; j++)
            {
                cin >> W;
                g[i][j] = g[j][i] = W; 
            }   
        }
        bool o = 0;
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                {
                    if(g[i][k] + g[k][j] < g[i][j] && i != j)
                    {
                        o = 1;
                        break;
                    }
                    if(g[i][k] + g[k][j] == g[i][j] && i != j)
                        adj[i][j] = 0;
                }   

        if(o) cout << "Need better measurements.\n";
        else
        {
            vp ans;
            for(int i = 0; i < n-1; i++)
            {
                for(int j = i+1; j < n; j++)
                {
                    if(!adj[i][j]) continue;
                    ans.push_back({i, j});
                    
                }   
            }
            sort(ALL(ans));
            cout << ans.size() << "\n";
            for(auto it : ans)
                cout << it.first+1 << " " << it.second+1 << " " << g[it.first][it.second] << "\n";
        }
        cout << "\n";
    }
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
