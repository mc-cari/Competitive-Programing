#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1924
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    for(int T=1;T<=t;T++)
    {
        int n,d,m,u,v,c,p,e,x,sum=0,o=0;
        cin>>n>>d>>m;
        vector<tuple<int,int,int,int,int> >g;
        vector<int>z;
        for(int i=0;i<m;i++)
        {
            cin>>u>>v>>c>>p>>e;
            g.push_back(make_tuple(p,u,v,c,e));
        }
        sort(g.begin(),g.end());
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(i==n-1)
                x=0;
            sum+=x;
            z.push_back(x);
        }
        if(sum==0)
        {
            cout<<"Case #"<<T<<": 0\n";
            continue;
        }
        int l=0,r=m-1,P;
        while(l<=r)
        {
            P=(l+r)/2;
            Dinic din(n*d+2);
            for(int i=0;i<n;i++)
            {
                din.add_edge(n*d,i,z[i]);
            }
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<d;j++)
                {
                    for(int q=j+1;q<d;q++)
                    {
                        din.add_edge(i+n*j,i+n*q,10000);
                    }
                }
            }
            din.add_edge(n-1+n*(d-1),n*d+1,10000);
            for(int i=0;i<=P;i++)
            {
                tie(p,u,v,c,e)=g[i];
                if(e==d-1 && v==n)
                    din.add_edge(u-1+e*n,n*d+1,c);
                else if(e==d-1 &&v!=n)
                {continue;cout<<"Hola";}
                else
                    din.add_edge(u-1+e*n,v-1+(e+1)*n,c);
            }
            //cout<<din.max_flow(n*d,n*d+1)<<" "<<sum<<" "<<P<<endl;
            if(din.max_flow(n*d,n*d+1)==sum)
            {
                r=P-1;
                o=1;
            }
            else l=P+1;

        }
        //cout<<r<<" "<<l<<" "<<P<<endl;
        cout<<"Case #"<<T<<": ";
        if(o)cout<<get<0>(g[l])<<"\n";
        else cout<<"Impossible\n";
    }
}
