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

//https://vjudge.net/problem/ZOJ-1298

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
    ll n, m, T=1;
    while(cin >> n >> m && (n + m))
    {
        vector<string>S;
        string s;
        for(int i = 0; i < n; i++)
        {
            cin >> s;
            S.push_back(s);
        }
        Dinic din(n*m*2+3);
        ll input = 0, in=0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(S[i][j] != '#')continue;
                input++;
                din.add_edge(n*m*2, i*m + j, 1);
                if(i > 0 && S[i-1][j] == '#'){in++;
                    din.add_edge(i*m + j, (i-1)*m + j + n*m, INF);}
                if(j > 0 && S[i][j-1] == '#'){in++;
                    din.add_edge(i*m + j, i*m + j-1 + n*m, INF);}
                if(i < n-1 && S[i+1][j] == '#'){in++;
                    din.add_edge(i*m + j, (i+1)*m + j + n*m, INF);}
                if(j < m-1 && S[i][j+1] == '#'){in++;
                    din.add_edge(i*m + j, i*m + j+1 + n*m, INF);}
                din.add_edge(i*m + j + n*m, n*m*2+1, 1);
            }

        }
        cout<<"Case "<<T<<": ";

        if(din.max_flow(n*m*2, n*m*2+1) == input)cout<<"Possible\n";
        else cout<<"Impossible\n";
        T++;
    }    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}
