#include "../Header.cpp"

// All toposort orderings
vector<vl> g;
ll in;
vl indegree, vis;
vl sorted;
vector<char> ans;
bool possible;
void toposort()
{
    bool flag = 0;

    for(int i = 0; i < in; i++)
    {
        if(indegree[i] == 0 && !vis[i])
        {
            sorted.push_back(i);
            

            for(auto it : g[i])
                indegree[it]--;
            vis[i] = 1;
            toposort();
            vis[i] = 0;
            sorted.pop_back();

            for(auto it : g[i])
                indegree[it]++;
            flag = 1;
        }
    }
    if(!flag && sorted.size() == in)
    {
        possible = 1;
        for(int i = 0; i < in; i++)
        {
            if(i > 0) cout << " ";
            cout << ans[sorted[i]];
        }
        cout << "\n";
    }
}

int main()
{
	ll v,x,y,e,a,b,in=0;
	pll h;
	cin>>v >> e;
	vector<vl > g(v, vl(0));
	for(int i = 0; i < e; i++)
    {
        cin >> x >> y;
        g[x].push_back(y);
    }

    //set indegrees
    vl indegree(v, 0);
    vl sorted;
    for(int i=0; i < v; i++)
    {
        for(auto it : g[i])
            indegree[it]++;
    }
    queue<ll> q;
    //agregar par a cola para tener los paquetes o niveles de profundidad, sumar
    for(int i = 0; i < v; i++)
        if(indegree[i] == 0)
            q.push(i);

    while(!q.empty()){

        ll t = q.front();
        q.pop();

        for(auto it : g[t]){

            if(--indegree[it] == 0)
                q.push(it);
        }
    }
}
