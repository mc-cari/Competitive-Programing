#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e18
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://www.urionlinejudge.com.br/judge/es/problems/view/2354

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

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  ll n, x, y;
  cin >> n;
  vp c;
  for(int i = 0; i < n; i++)
  {
    cin >> x >> y;
    c.push_back({x, y});
  }
  ll ans = n;
  for(int i = 0; i < n; i++)
  {
    Dinic din(n*2 + 3);
    //obj: votes to wolf
    //f: votes left
    ll obj = 0, f = n-1;
    for(int j = 0; j < n; j++)
    {
      if(j == i)continue;
      if(c[j].first == i+1 || c[j].second == i+1)
      {
        obj++;
        f--;
      } 
      else if (j != i)
      {
        din.add_edge(j, n + c[j].first-1, 1);
        din.add_edge(j, n + c[j].second-1, 1);
      }
    }


    for(int j = 0; j < n; j++)
    {
      if(j == i)continue;
      din.add_edge(2*n+1, j, 1);

      if(j == c[i].first-1 || j == c[i].second-1)
        din.add_edge(n + j, 2*n+2, obj-2);
      else
        din.add_edge(n + j, 2*n+2, obj-1);
    }
    if(din.max_flow(2*n+1, 2*n+2) == f)ans--;

    
  }
  cout << ans << "\n";



  
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
