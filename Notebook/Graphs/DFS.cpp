#include "../Header.cpp"

vl depht, v, nodes;
vl ind;
vector <vl>g;
void dfs(int t)
{
    if(!v[t]){
        nodes.push_back(t);
        v[t]=1;
        for(auto it : g[t]){

            if(!v[it])
            {
              depht[it]=depht[t]+1;
              dfs(it);
            }
            
        }
        nodes.pop_back();
    }
}

int main()
{
	ll n, x, y, e, a, b, i n =0;
	cin >> n >> e;
	vector<vl> g(n, vl(0));
	rep(i, e)
    {
        cin >> x >> y;
        g[x].push_back(y);
    }
	vl v(n, 0);
    vl d(n,INF);
    d[inicio]=0;
    stack<ll> q;
    q.push(inicio);
    while(!q.empty()){

        ll t = q.top();
        q.pop();
        if(v[t]) continue;

        v[t] = 1;
        for(auto it : g[t]){

            if(!v[it])
            {
                d[it] = d[t]+1;
                q.push(it);
            }
        }

    }

	return 0;
}
