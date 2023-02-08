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

// https://dmoj.ca/problem/ioi11p4

int travel_plan(int N, int M, int R[][2], int W[], int K, int E[])
{
    vector<vp>g(N, vp());
    for(int i = 0; i < M; i++)
    {
        ll x = R[i][0], y = R[i][1], d = W[i];
        g[x].push_back({d, y});
        g[y].push_back({d, x});
    }

    vl d(N, INF);
    vl vis(N, 0);
    priority_queue<pll, vp, greater<pll> > q; //from low to high
    for(int i = 0; i < K ; i++)
    {
        q.push({0, E[i]});
        d[E[i]] = 0;

        vis[E[i]] = 1;
    }
    
    while(!q.empty()){
        
        ll w, u;
        tie(w, u) = q.top();
        q.pop();

        
        if(vis[u] == 2) continue;
        vis[u]++;
        if(vis[u] == 1) continue;
       
        d[u] = w;

        for(auto it : g[u])
        {
            if(vis[it.second] == 2)continue;
            q.push({w + it.first, it.second});

        }
    }

    return d[0];
    
}


int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll N, M, K;
    cin >> N >> M >> K;
    int R[M][2], W[M];
    for(int i = 0; i < M; i++)
    {
        cin >> R[i][0] >> R[i][1];
    }
    for(int i = 0; i < M; i++)
    {
        cin >> W[i];
    }
    int E[K];
    for(int i = 0; i < K; i++)
    {
        cin >> E[i];
    }
    cout << travel_plan(N, M, R, W, K, E) << "\n";

    
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
