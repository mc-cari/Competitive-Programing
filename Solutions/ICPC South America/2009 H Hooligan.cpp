#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.urionlinejudge.com.br/judge/es/problems/view/1394

struct Dinic {
    struct edge {
        int to, rev;
        ll f, cap;
    };

    vector<vector<edge>> g;
    vector<ll> dist;
    vector<int> q, work;
    int n, sink;

    bool bfs(int start, int finish) {
        dist.assign(n, -1);
        dist[start] = 0;
        int head = 0, tail = 0;
        q[tail++] = start;
        while (head < tail) {
            int u = q[head++];
            for (const edge &e : g[u]) {
                int v = e.to;
                if (dist[v] == -1 and e.f < e.cap) {
                    dist[v] = dist[u] + 1;
                    q[tail++] = v;
                }
            }
        }
        return dist[finish] != -1;
    }

    ll dfs(int u, ll f) {
        if (u == sink)
            return f;
        for (int &i = work[u]; i < (int)g[u].size(); ++i) {
            edge &e = g[u][i];
            int v = e.to;
            if (e.cap <= e.f or dist[v] != dist[u] + 1)
                continue;
            ll df = dfs(v, min(f, e.cap - e.f));
            if (df > 0) {
                e.f += df;
                g[v][e.rev].f -= df;
                return df;
            }
        }
        return 0;
    }

    Dinic(int n) {
        this->n = n;
        g.resize(n);
        dist.resize(n);
        q.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edge a = {v, (int)g[v].size(), 0, cap};
        edge b = {u, (int)g[u].size(), 0, 0}; //Poner cap en vez de 0 si la arista es bidireccional
        g[u].push_back(a);
        g[v].push_back(b);
    }

    ll max_flow(int source, int dest) {
        sink = dest;
        ll ans = 0;
        while (bfs(source, dest)) {
            work.assign(n, 0);
            while (ll delta = dfs(source, LLONG_MAX))
                ans += delta;
        }
        return ans;
    }
};


int main() {
    ios_base:: sync_with_stdio(0);
    cin.tie(0);
    ll n, m, g;
    while(cin >> n >> m >> g && (n+m+g))
    {

        vl punt(n, 0), pend(n, m*(n-1));
        vector<vl> match(n, vl(n, m));
        for(int i = 0; i < g; i++)
        {

            ll l, r;
            char s;
            cin >> l >> s >> r;
            pend[r]--;
            pend[l]--;
            match[l][r]--;
            match[r][l]--;
            if(s == '<')
                punt[r]+= 2;
            else if(s == '>')
                punt[l]+= 2;
            else
            {
                punt[l]++;
                punt[r]++;
            }
        }
        
        punt[0] += pend[0]*2;
        Dinic din(n+n*(n+1)/2+2);
        ll fin = n+n*(n+1)/2 + 1;
        ll in = n, input = 0;
        bool o = 0;
        for(int i = 1; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                din.add_edge(0, in, 2*match[i][j]);
                input += 2*match[i][j];
                din.add_edge(in, i, INF);
                din.add_edge(in, j, INF);
                in++;
            }
            if(punt[0] - punt[i] -1< 0)o=1;
            din.add_edge(i, fin, punt[0] - punt[i]-1);
        }
        if(o)cout<<"N\n";
        else if(input == din.max_flow(0,fin))cout<<"Y\n";
        else cout<<"N\n";

    }    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}
