#include <bits/stdc++.h>
using namespace std;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1302
typedef long long int ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
vl D;
ll maxlog2(ll x){
    return (31 - __builtin_clz(x));
}
struct SparseTableLCA
{
    ll maxlg;
    vector<vl >SP;
    SparseTableLCA(vl&A)
    {
        ll n=A.size();
        SP.clear();
        SP.push_back(A);
        ll maxlog = 31 - __builtin_clz(n);
        maxlg=maxlog;
        for(ll i=1;i<=maxlog;i++)
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
    {
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
int main() {
    int n,x,y;
    while(cin>>n)
    {
        vector<vl > dfs(n,vl(0));
        vector<vl > grafo(n,vl(0));
        vector<vl > agrafo(n,vl(0));
        vl ID(n,0);
        vl ID2(n,0);
        ll cont=0;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            dfs[i].push_back(x-1);
            dfs[x-1].push_back(i);
            grafo[i].push_back(x-1);
            agrafo[x-1].push_back(i);
        }

        vector<bool> visitado(n,false);
        for(int i=0;i<n;i++)
        {
            ll inicio=i;
            if(!visitado[inicio]){
                cont++;
                stack<ll> q;
                q.push(inicio);
                while(!q.empty()){
                    ll t=q.top();
                    ID[t]=cont;
                    q.pop();
                    if(!visitado[t]){
                        visitado[t]=true;
                        for(ll i=0;i<dfs[t].size();i++){
                            if(!visitado[dfs[t][i]])
                            {
                                q.push(dfs[t][i]);
                            }
                        }
                    }
                }
            }
        }
        vl tam(cont+1,0);
        /*for(int i=0;i<n;i++)
        {
            cout<<i+1<<" "<<ID[i]<<endl;
        }*/
        ll in=1;
        vl loop(n,0);
        visitado.clear();visitado.assign(n,0);
        for(int i=0;i<n;i++)
        {
            if(in==ID[i])
            {
                in++;
                ll nodo=i;
                stack<ll>p;
                while(!visitado[nodo])
                {
                    visitado[nodo]=1;
                    p.push(nodo);
                    nodo=grafo[nodo][0];
                }
                ll co=1;
                while(1)
                {
                    loop[p.top()]=co;
                    if(p.top()==nodo)break;
                    co++;
                    p.pop();
                }
                tam[ID[i]]=co;
            }
        }
        cont=0;
        D.clear();D.resize(n,INF);
        vl parent(n,-1);
        vl ori(n,-1);
        visitado.clear();visitado.assign(n,0);
        for(int t=0;t<n;t++)
        {
            if(loop[t])
            {
                cont++;
                queue<ll> q;
                q.emplace(t);
                D[t]=0;
                while(!q.empty()){
                    ll k=q.front();q.pop();
                    ID2[k]=cont;
                    if(!visitado[k]){
                        visitado[k]=true;
                        for(ll i=0;i<agrafo[k].size();i++)
                        {
                                if(!visitado[agrafo[k][i]]&&loop[agrafo[k][i]]==0)
                                {
                                    parent[agrafo[k][i]]=k;
                                    D[agrafo[k][i]]=D[k]+1;
                                    ori[agrafo[k][i]]=t;
                                    q.push(agrafo[k][i]);
                                }
                        }
                    }
                }
            }
        }
        SparseTableLCA AC(parent);
        /*for(int i=0;i<n;i++)
        {
            cout<<i+1<<" "<<D[i]<<" "<<parent[i]<<endl;
        }*/
        ll q;
        cin>>q;
        for(int i=0;i<q;i++)
        {
            cin>>x>>y;x--;y--;
            if(ID[x]!=ID[y])
            {
                cout<<"-1\n";
            }
            else if(loop[x]==0&&loop[y]==0&&ID2[x]==ID2[y])
            {
                cout<<AC.Dist(x,y)<<"\n";
            }
            else
            {
                ll sum=0;
                if(loop[x]==0)
                {
                    sum+=D[x];
                    x=ori[x];
                }
                if(loop[y]==0)
                {
                    sum+=D[y];
                    y=ori[y];
                }
                //cout<<sum<<" "<<x<<" "<<y<<endl;
                sum+=min(abs(loop[x]-loop[y]),tam[ID[x]]-abs(loop[x]-loop[y]));
                cout<<sum<<"\n";                //dist circular;
            }
        }
    }
}
