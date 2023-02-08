#include "../Header.cpp"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int v,e,x,y,w,r;
    cin >> v >> e >> r;
    pll h;
    vl d(v, INF);
    d[r] = 0;//nodo de inicio
    vector<vector<pll> > g(v, vector<pll> (0));

	for(int i = 0 ;i < e; i++)
    {
        cin >> x >> y >> w;
        h.first = y;
        h.second = w;
        g[x].push_back(h);
    }
    /*
    inequations solver
    v - u <= p
    g[u].push_back({v, p});
    g[v].push_back({u, -1});
    d[s] = 0
    for i in v: g[s].push_back({i, 0})
    */
   
	rep(i, v-1)
    {
        bool mod = 0;
        rep(j, v)
            if(d[j] != INF)
                for(auto it : g[j])
                {
                    d[it.first] = min(d[it.first], d[j] + it.second);
                    mod = 1;
                }
        if(mod == 0)
            break;
    }
    bool cyc = 0;
    rep(j, v)
        for(auto it : g[j])
            if(d[j] < INF && d[it.first] > d[j] + it.second)
                cyc = 1;


    // From :https://github.com/stevenhalim/cpbook-code/blob/master/ch4/sssp/bellman_ford_moore.cpp
    // Faster but doesnt support negative cycles
    // SPFA from source S
    vl dist(v, INF); dist[s] = 0;                  // INF = 1e9 here
    queue<int> q; q.push(s);                       // like BFS queue
    vl in_queue(v, 0); in_queue[s] = 1;            // unique to SPFA
    while (!q.empty()) {
        int u = q.front(); q.pop(); in_queue[u] = 0; // pop from queue
        for (auto it : g[u]) {                 // C++17 style
        if (dist[u]+it.first >= dist[it.second]) continue;        // not improving, skip
        dist[it.second] = dist[u]+it.first;                       // relax operation
        if (!in_queue[it.second]) {                        // add to the queue
            q.push(it.second);                               // only if v is not
            in_queue[it.second] = 1;                         // already in the queue
        }
        }
    }
    
	return 0;
}
