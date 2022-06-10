#include "../Header.cpp"

int main()
{
	ll v,x,y,e;
	pll h;
	cin >> v >> e;
	vector<vl > g(v, vl(0));
	for(int i = 0; i < e; i++)
    {
        cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
    }
    vl indegree(v, 0);
    vector<pll> sorted;
    for(int i = 0; i < v; i++)
    {
        for(int j = 0; j < g[i].size(); j++)
        {
            indegree[g[i][j]]++;
        }
    }
    ll r = 0;
    priority_queue<pll,vector<pll>,greater<pll> >d;
    for(int i = 0; i < v; i++)
        if(indegree[i] == 0)
            d.emplace(i, r);
    vl sol;
    vl im(v,0);
    while(!d.empty())
    {
        pll u = d.top();
        ll t = u.first;
        d.pop();
        sol.push_back(u.first+1);
        for(auto it : g[t])
        {
            indegree[it]--;
            if(indegree[it] == 0)
                d.emplace(it, 0);
        }
    }

    for(int i = 0; i < sol.size(); i++)
    {
        cout<<sol[i]<<" ";
    }


	return 0;
}
