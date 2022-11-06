#include "../Header.cpp"

// From: https://cp-algorithms.com/graph/desopo_pape.html

int main()
{
	ll v,x,y,e;
	pll h;
  	vector<ll>b;
	cin >> v >> e;
	vector<vp > g(v, vp (0));
	vl peso(v, INF);

    int w;
	for(ll i = 0; i < e; i++)
	{
		cin >> x >> y >> w;
		
		g[x-1].push_back({w, y-1});
		g[y-1].push_back({w, x-1});
	}
	ll s, t;

    vl d(v, INF);
    d[s] = 0;
    vl m(v, 2);
    deque<ll> q;
    q.push_back(s);
    p.assign(v, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        m[u] = 0;
        for (auto it : g[u]) {
            if (d[it.second] > d[u] + it.first) {
                d[it.second] = d[u] + it.first;
                p[it.second] = u;
                if (m[it.second] == 2) {
                    m[it.second] = 1;
                    q.push_back(it.second);
                } else if (m[it.second] == 0) {
                    m[it.second] = 1;
                    q.push_front(it.second);
                }
            }
        }
    }

	return 0;
}
