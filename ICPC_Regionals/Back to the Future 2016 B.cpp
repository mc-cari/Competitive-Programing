#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://www.urionlinejudge.com.br/judge/es/problems/view/2346
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N,M,A,B,x,y;
    cin>>N>>M>>A>>B;
    vl degree(N,0);
    vector<int>erased(N,0);
    vector<vl>grafo(N,vl(0));
    for(int i=0;i<M;i++)
    {
        cin>>x>>y;
        degree[x-1]++;
        degree[y-1]++;
        grafo[x-1].push_back(y-1);
        grafo[y-1].push_back(x-1);
    }
    ll total=N;
    bool o=1;
    set<pll>lista;
    for(int i=0;i<N;i++)
    {
        lista.insert(make_pair(degree[i],i));
    }
    while(total>0)
    {
        ll v;
        set<pll>::iterator it=lista.begin();
        set<pll>::reverse_iterator ot=lista.rbegin();
        if((*it).first<A)
        {
            v=(*it).second;
        }
        else if(total-1-(*ot).first<B)
        {
            v=(*ot).second;
        }
        else break;
        lista.erase(make_pair(degree[v],v));
        for(int j=0;j<grafo[v].size();j++)
        {
            if(erased[grafo[v][j]])continue;
            lista.erase(make_pair(degree[grafo[v][j]],grafo[v][j]));
            degree[grafo[v][j]]--;
            lista.insert(make_pair(degree[grafo[v][j]],grafo[v][j]));
        }
        erased[v]=1;
        total--;
    }
    cout<<total<<"\n";
    return 0;
}
