#include<bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
//https://www.urionlinejudge.com.br/judge/es/problems/view/1751

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	ll v,x,y,f,k;
	pll h;

	cin>>v>>f;
	vector<int>c;
	ll sum=0;
	map<pll,bool >ver;
	vector<vector<pll> > grafo(v,vector<pll> (0));
	vector<vector<pll> > grafo2(v,vector<pll> (0));
	for(int i=0;i<v-1;i++)
    {
        cin>>x>>y>>k;
        y--;
        x--;
        h.first=k;
        h.second=x;
        grafo[y].push_back(h);
        h.second=y;
        grafo2[x].push_back(h);
    }
    ll inicio=0;
    for(int i=0;i<f;i++)
    {
        cin>>x;
        x--;
        c.push_back(x);
    }
    vector<bool> visitado(v,false);

    for(int i=0;i<f;i++)
    {
        if(!visitado[c[i]]){
        inicio=c[i];
		stack<ll> q;
		q.push(inicio);
		while(!q.empty()){

		    ll t=q.top();
		    q.pop();
		    if(t==0)
            {
                break;
            }
            if(!visitado[t])
            {
                visitado[t]=true;
            }
            for(ll i=0;i<grafo[t].size();i++){
                h.second=grafo[t][i].second;
                h.first=t;
                if(ver[h])
                {
                    continue;
                }
                    ver[h]=1;
                    sum+=grafo[t][i].first;
                    q.push(grafo[t][i].second);
            }

		}
        }
    }
    vl dist(v,INF);
    inicio=0;
    dist[inicio]=0;
    queue<ll> q;
    q.push(inicio);
    while(!q.empty()){
        ll t=q.front();
        q.pop();

            for(ll i=0;i<grafo2[t].size();i++){

                h.first=grafo2[t][i].second;
                h.second=t;
                if(!ver[h])
                {
                    continue;
                }
                dist[grafo2[t][i].second]=dist[t]+grafo2[t][i].first;
                q.push(grafo2[t][i].second);
            }
    }
    ll maxi=-1;
    for(int i=0;i<f;i++)
    {
        if(dist[c[i]]>maxi)maxi=dist[c[i]];
    }
    cout<<sum-maxi<<endl;

	return 0;
}
