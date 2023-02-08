// Time Complexity:
// - general worst case: O (|E| * |V|^2)
// - unit capacities: O( min( V^(2/3), sqrt(E) ) )
// - Bipartite graph (unit capacities) + source & sink (any capacities): O(E sqrt V)

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

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

// usage
int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    ll R,C,a,b;
    while(cin>>R>>C)
    {
        Dinic din(R*C+2);
        char s[R][C];
        int in[R][C];
        ll p=1,en=0,out=0;
        for(int i=0;i<R;i++)
            for(int j=0;j<C;j++)
                {
                    in[i][j]=p;
                    p++;
                    cin>>s[i][j];
                }
        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                if((i+j)%2!=0)
                {
                    if (s[i][j]=='o')
                    {
                        out++;
                        din.add_edge(in[i][j],R*C+1,1);
                    }
                    else
                    {
                        din.add_edge(in[i][j],R*C+1,2);
                        out+=2;
                    }
                    continue;
                }
                if (s[i][j]=='o')
                {

                    din.add_edge(0,in[i][j],1);
                    en++;
                }
                else
                {
                    din.add_edge(0,in[i][j],2);
                    en+=2;
                }
                if(i>0)
                {
                    din.add_edge(in[i][j],in[i-1][j],100);
                }
                if(j>0)
                {
                    din.add_edge(in[i][j],in[i][j-1],100);
                }
                if(i<R-1)
                {
                    din.add_edge(in[i][j],in[i+1][j],100);
                }
                if(j<C-1)
                {
                    din.add_edge(in[i][j],in[i][j+1],100);
                }
            }
        }
        if(en==din.max_flow(0,R*C+1) && out==en)
        {
            cout<<"Y\n";
        }
        else
            cout<<"N\n";
    }
    return  0;

}
