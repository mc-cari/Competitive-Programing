#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://www.spoj.com/problems/LCA/en/

ll maxlog2(ll x){
    return (63 - __builtin_clzll(x));
}
struct SparseTableLCA
{
    ll maxlg;
    vector<vl >SP;
    vector<vl >MN;
    vl D;
    SparseTableLCA(vector<vl >& g, ll ini)
    {
        ll n = g.size();
        vl vis(n, 0);
        vl parent(n,-1);
        D.resize(n, INF); D[ini]=0;
        queue<ll> q;
        q.emplace(ini);
        while(!q.empty()){
            ll k=q.front();q.pop();
            if(!vis[k]){
                vis[k]=1;
                for(ll i=0; i < g[k].size(); i++)
                {
                    if(!vis[g[k][i]])
                    {
                        parent[g[k][i]]=k;
                        D[g[k][i]]=D[k]+1;
                        q.push(g[k][i]);
                    }
                }
            }
        }

        SP.clear();
        SP.push_back(parent);
        maxlg=maxlog2(n);
        for(ll i=1; i<= maxlog2(n);i++)
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
    }
    ll level(ll a,ll n)// a=distancia
    {// eleva n una distancia a
        while(D[n]!=a)
        {
            n=SP[maxlog2(D[n]-a)][n];
        }
        return n;
    }
    ll LCA(ll u,ll v)
    {
        ll x,y;
        if(D[u]>D[v])
        {
            x=u;y=v;
        }
        else
        {
           x=v;y=u;
        }
        if(D[x]!=D[y]){
            x = level(min(D[x],D[y]),x);
        }
        if(x==y)return x;
        for(ll i = maxlg;i>=0;i--)
        {
            if(SP[i][x]!=SP[i][y]&&SP[i][x]!=-1)
            {
                x=SP[i][x];
                y=SP[i][y];
            }
        }
        return SP[0][x];
    }
    ll Dist(ll u,ll v)
    {
        return D[u]+D[v]-2*D[LCA(u,v)];
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t, cas= 1;
    cin >> t;
    while(t--)
    {
        ll n, x;
        
        cin >> n;
        vector<vl> g(n, vl(0));
        
        for(int i = 0; i < n; i++)
        {
            ll m;
            cin >> m;
            for(int j = 0; j < m; j++)
            {
                cin >> x;
                g[i].push_back(x-1);
                g[x-1].push_back(i);
            }
            
        }
        
        SparseTableLCA LCA(g, 0);
        ll q;
        cin >> q;
        cout<<"Case "<<cas<<":\n";
        cas++;
        while(q--)
        {
            ll v, w;
            cin >> v >> w;
            v--; w--;
            cout<<LCA.LCA(v, w)+1<<"\n";
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
