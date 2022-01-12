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

#define ff first
#define ss second
typedef pair<int,int> ii;
vector<int> D, L, vis;
vector<vl> g, g2;
stack<ii> s; 
vl comps;
ll in;

//https://www.beecrowd.com.br/judge/es/problems/view/1314

void dfs(int u, int p, int d) {
    D[u] = L[u] = d;
    vis[u] = 1;
    for(auto v : g[u]) {
        if (v == p) continue;
        if (D[v] == -1) {
            dfs(v, u, d+1);
            if (L[v] > D[u]) 
            {
                
                g2[u].push_back(v);
                g2[v].push_back(u);
            }
            L[u] = min(L[u], L[v]); 
        } else L[u] = min(L[u], D[v]);
    }
}

void dfs2(ll u, ll p)
{
    comps[u] = in;
    vis[u] = 1;
    for(auto it : g2[u])
    {
        if(it == p) continue;
        dfs2(it, u);
    }
}


int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll r, c, q;
    while(cin >> r >> c >> q && (r + c + q))
    {
        g.assign(r, vl());
        g2.assign(r, vl());
        vis.assign(r, 0);
        L.assign(r, 0);
        D.assign(r, -1);
        comps.assign(r, -1);
        ll x, y;
        for(int i = 0; i < c; i++)
        {
            cin >> x >> y; x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);

        }
        for(int i = 0; i < r; i++)
        {
            if(vis[i])continue;
            dfs(i, -1, 0);
        }
        in = 0;
        vis.assign(r, 0);
        for(int i = 0; i < r; i++)
        {
            if(vis[i])continue;
            dfs2(i, -1);
            in++;
        }

        for(int i = 0; i < q; i++)
        {
            cin >> x >> y; x--; y--;
            if(comps[x] == comps[y]) cout << "Y\n";
            else cout << "N\n";
        }
        cout << "-\n";
        
        
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
