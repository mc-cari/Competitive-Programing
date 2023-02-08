#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://acm.timus.ru/problem.aspx?space=1&num=1752

ll maxlog2(ll x){
    return (63 - __builtin_clzll(x));
}
struct SparseTableLCA
{
    ll maxlg;
    vector<vl >SP;
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
                for(ll i=0;i<g[k].size();i++)
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
        for(ll i=1;i<=maxlog2(n);i++)
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
    ll query(ll u, ll v, ll d)
    {
        if(Dist(u, LCA(u, v)) < d)
            return level(D[v] - (Dist(u, v) - d), v);

        else
            return level(D[u] - d, u);
    }
    ll level(ll a,ll n)// a=distancia
    {// lleva n a la profundidad a
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
    
    ll n, Q, x, y, dia1, dia2;
    cin >> n >> Q;
    vector<vl> g(n, vl(0));
    for(int i = 0; i < n-1; i++)
    {
        cin >> x >> y;
        g[x-1].push_back(y-1);
        g[y-1].push_back(x-1);
    }
    

    queue<ll> q;
    q.push(0);
    vl vis(n, 0);
    vl dis(n, 0);
    dis[0] = 0;
    ll maxi = -1, maxin;
    while(!q.empty())
    {
        ll t = q.front();
        if(dis[t] > maxi)
        {
            maxi = dis[t];
            maxin = t;
        }
        q.pop();
        if(!vis[t])
        {
            vis[t] = 1;
            for(auto it: g[t])
            {
                if(!vis[it]){
                    dis[it] = dis[t]+1;
                    q.push(it);
                }
            }
        }
    }
    dia1 = maxin;

    q.push(dia1);
    vis.assign(n, 0);
    dis.assign(n, 0);
    dis[dia1] = 0;
    maxi = -1;
    while(!q.empty())
    {
        ll t = q.front();
        if(dis[t] > maxi)
        {
            maxi = dis[t];
            maxin = t;
        }
        q.pop();
        if(!vis[t])
        {
            vis[t] = 1;
            for(auto it: g[t])
            {
                if(!vis[it]){
                    dis[it] = dis[t]+1;
                    q.push(it);
                }
            }
        }
    }
    SparseTableLCA LCA(g, 0);
    dia2 = maxin;
    while(Q--)
    {
        ll d;
        cin>> x >> d;
        if(LCA.Dist(x-1, dia1) < d && LCA.Dist(x-1, dia2) < d)cout<<"0\n";
        else if(LCA.Dist(x-1, dia1) >= d)
        cout<< LCA.query(x-1, dia1, d)+1<<"\n";//<<" "<<LCA.Dist(x-1, LCA.query(x-1, dia1, d)) <<"\n";
        else
        cout<< LCA.query(x-1, dia2, d)+1<<"\n"; //<<" "<<LCA.Dist(x-1, LCA.query(x-1, dia2, d))<<"\n";
        
    }
    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
