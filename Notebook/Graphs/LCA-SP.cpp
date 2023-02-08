#include "../Header.cpp"

struct UF{
    vector<ll>p,r;

    void makeSet(ll x)//cambiar cuando no es ll
    {

        p.push_back(x);
        r.push_back(0);
    }
    ll find(ll x)
    {
        if(p[x]==x) return x;
        else return p[x]=find(p[x]);
    }
    void join(ll x,ll y)
    {
        x=find(x);
        y=find(y);
        if(x!=y)
        {
            if(r[x]>=r[y])
            {
                if(r[x]==r[y])
                    r[x]++;
                p[y]=x;
            }
            else p[x]=y;
        }
    }
};
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
    SparseTableLCA(vector<vl>& g, ll ini)
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
        maxlg = 63 - __builtin_clzll(n);

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
    ll level(ll a,ll n)// a=distancia
    {// lleva n a la profundidad a
        while(D[n] != a)
            n = SP[maxlog2(D[n]-a)][n];
        return n;
    }
    ll LCA(ll u,ll v)
    {
        ll x = u, y = v;
        if(D[u] <= D[v]) swap(x, y);

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


// D[i] -> �profundidad de i
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n,m,x,y,h,Q,w;
    cin>>n>>m;
    vector<vp> grafo(n,vp(0));
    UF ds;
    vector<tuple<ll,ll,ll,ll> >c;
    vector<tuple<ll,ll,ll> >C;
    tuple<ll,ll,ll,ll>H;
    for(ll i=0;i<n;i++)
        ds.makeSet(i);
    for(ll i=0;i<m;i++)
    {
        cin>>get<1>(H)>>get<2>(H)>>get<0>(H);
        get<3>(H)=i;
        c.push_back(H);
        C.push_back(make_tuple(get<0>(H),get<1>(H),get<2>(H)));
    }
    sort(c.begin(),c.end());
    vl M(m,0);
    ll sum=0;
    for(ll i=0;i<m;i++)
    {
        ll x,y,v;
        x=get<1>(c[i])-1;
        y=get<2>(c[i])-1;
        v=get<0>(c[i]);
        if(ds.find(x)!=ds.find(y))
        {
            M[get<3>(c[i])]=1;
            sum+=v;
            grafo[x].push_back(make_pair(v,y));
            grafo[y].push_back(make_pair(v,x));
            ds.join(x,y);
        }
    }
    ll ini=0;
    for(ll i=0;i<n;i++)
    {
        if(grafo[i].size()==1)
        {
            ini=i;
            break;
        }
    }
    
    // Padres, aristas
    SparseTableLCA AC(g, ini);
    for(ll i=0;i<m;i++)
    {
        ll x,y,v;
        x=get<1>(C[i])-1;
        y=get<2>(C[i])-1;
        v=get<0>(C[i]);
        if(M[i])
            cout<<sum<<"\n";
        else
        {
            cout<<sum+v-AC.maxL(x,y)<<"\n";
        }
    }
    return 0;
}
