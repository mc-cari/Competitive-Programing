#include "../Header.cpp"

int main()
{
	ll v, x, y, e;
	pll h;
  	vector<ll>b;
	cin >> v >> e;
	vector< vp > g(v, vp (0));
	
    
	for(ll i = 0; i < e; i++)
	{
		ll w;
		cin >> x >> y >> w;
		
		g[x-1].push_back({w, y-1});
		g[y-1].push_back({w, x-1});
	}

	vl d(v, INF);
	priority_queue<pll, vp, greater<pll> > q; //from low to high
	ll s, t;

	q.push({0, s});
	d[s] = 0;

	while(!q.empty()){

		ll w, u;
		tie(w, u) = q.top();
	    q.pop();
		
		if(w > d[u])continue;
		for(auto it : g[u])
		{
		   	if(d[it.second] > w + it.first)
		   	{
		   		d[it.second] = w + it.first;
		   		q.push({d[it.second], it.second});
			}
	  }
	}

	return 0;
}
