#include "../Header.cpp"

ll maxlog2(ll x){
    return (63 - __builtin_clzll(x));
}

// To minimize diameter, connect the center of the diameter of two trees
// min(diam1, diam2, dia1+dia2+1)  dia1 = diam1/2  (if diameter odd)+ 1

struct SparseTableLCA
{
    ll maxlg;
    vector<vl >SP;
    vector<vl >MN;
    vl D;
    SparseTableLCA(vector<vl>& g, ll ini=0)
    {
        ll n = g.size();
        vl vis(n,0), parent(n,-1);
        D.resize(n,INF);D[ini]=0;
        queue<ll> q;
        q.emplace(ini);
        while(!q.empty()){
            ll k=q.front();q.pop();
            if(!vis[k]){
                vis[k]=1;
                for(auto it : g[k])
                    if(!vis[it])
                    {
                        parent[it]=k;
                        D[it]=D[k]+1;
                        q.push(it);
                    }

            }
        }

        SP.clear();
        SP.push_back(parent);
        maxlg = maxlog2(n);

        repx(i, 1 , maxlg+1)
        {
            vl aux;
            rep(j, n)
            {
                if(SP[i-1][j]!=-1)
                aux.push_back(SP[i-1][SP[i-1][j]]);
                else aux.push_back(-1);
            }
            SP.push_back(aux);
        }
    }
    
    ll maxL(ll u,ll v)//arista largo maximo
    {
        ll a,b,x=LCA(u, v);
        if(u==x)a =- 1;
        else a = query(D[x], u);
        if(v==x)b =- 1;
        else b = query(D[x], v);
        return max(a, b);
    }
    ll query(ll a,ll n)
    {
        ll maxi=-1;
        while(D[n]!=a)
        {
            maxi = max(maxi, MN[maxlog2(D[n]-a)][n]);
            n=SP[maxlog2(D[n]-a)][n];
        }
        return maxi;
    }
    ll level(ll a, ll n) // up a to depth n
    {
        while(D[n] != a)
            n = SP[maxlog2(D[n]-a)][n];
        return n;
    }
    ll LCA(ll x,ll y)
    {
        if(D[x] <= D[y]) swap(x, y);

        if(D[x] != D[y])
            x = level(min(D[x], D[y]), x);

        if(x == y) return x;

        for(ll i = maxlg; i>=0; i--)
        {
            if(SP[i][x] != SP[i][y] && SP[i][x] != -1)
            {
                x = SP[i][x];
                y = SP[i][y];
            }
        }
        return SP[0][x];
    }
    ll Dist(ll u,ll v)
    {
        return D[u] + D[v] - 2*D[LCA(u, v)];
    }
    ll kth_fartest_node(ll u, ll v, ll d)
    {
        if(Dist(u, LCA(u, v)) < d)
            return level(D[v] - (Dist(u, v) - d), v);

        else
            return level(D[u] - d, u);
    }

    // move u k steps in path to v
    ll next_path(ll u, ll v, ll k){

      if(D[u] - D[LCA(u, v)] >= k) return level(D[u] - k, u);
      else return level(D[LCA(u, v)] + k - (D[u] - D[LCA(u, v)]), v);
    }
};


/* edge weight queries
SparseTableLCA(vector<vector<pll>>& g, ll ini)
    {
        ll n = g.size();
        vl vis(n,0), parent(n,-1), b(n,-1);
        D.resize(n,INF);D[ini]=0;
        queue<ll> q;
        q.emplace(ini);
        while(!q.empty()){
            ll k=q.front();q.pop();
            if(!vis[k]){
                vis[k]=1;
                for(auto it : g[k])
                    if(!vis[it.second])
                    {
                        b[it.second]=it.first;
                        parent[it.second]=k;
                        D[it.second]=D[k]+1;
                        q.push(it.second);
                    }
            }
        }

        SP.clear();
        SP.push_back(parent);
        maxlg= 63 - __builtin_clzll(n);
        for(ll i = 1; i <= maxlg; i++)
        {
            vl c;
            for(ll j=0;j<n;j++)
            {
                if(SP[i-1][j]!=-1)
                c.push_back(SP[i-1][SP[i-1][j]]);
                else c.push_back(-1);
            }
            SP.push_back(c);
        }
        MN.clear();
        MN.push_back(b);

        for(ll i=1;i<=maxlg;i++)
        {
            vl c;
            for(ll j=0;j<n;j++)
            {
                if(MN[i-1][j]!=-1)
                c.push_back(max(MN[i-1][SP[i-1][j]],MN[i-1][j]));
                else c.push_back(-1);
            }
            MN.push_back(c);
        }
    }
*/