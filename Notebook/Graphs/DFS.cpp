#include "../Header.cpp"

vl depht, v, nodes;
vl ind;
vector <vl>g;


ll dp[100000];

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


vector<ll> tam();

void dp(int t)
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


    vector<vl>g(n, vl(m)), v(n, vl(m, 0)), d(n, vl(m, 0));
    rep(i, n)
        rep(j, m)
        {
            cin >> g[i][j];
        }


    // implicit
    vl dx = {1, -1, 0, 0};
    vl dy = {0, 0, 1, -1};

    queue<pll> q;
    q.push({0, 0});
    while(!q.empty())
    {
        ll x, y;
        tie(x, y) = q.front();
        q.pop();

        if(vis[x][y])continue;
        rep(z, 4)
        {
            ll nx = x + dx[z], ny = y + dy[z];

            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            q.push({nx, ny});
        }

    }

	return 0;
}
