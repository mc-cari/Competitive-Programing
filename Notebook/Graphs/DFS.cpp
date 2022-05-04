#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())


vl depht, v, nodes;
vl ind;
vector <vl>g;
void dfs(int t)
{
    if(!v[t]){
        nodes.push_back(t);
        v[t]=1;
        for(ll i=0;i<g[t].size();i++){

            if(!v[g[t][i]])
            {
              depht[g[t][i]]=depht[t]+1;
              dfs(g[t][i]);
            }
            
        }
        nodes.pop_back();
    }
}

int main()
{
	ll n,x,y,e,a,b,in=0;
	cin>>n>>e;
	vector<vl > grafo(n,vl(0));
	for(int i=0;i<e;i++)
    {
        cin>>x>>y;
        grafo[x].push_back(y);
    }
    int inicio=0;


	vl v(n, 0);
    vl d(n,INF);
    d[inicio]=0;
    stack<ll> q;
    q.push(inicio);
    while(!q.empty()){

        ll t=q.top();
        q.pop();
        if(v[t]) continue;

        v[t]=1;
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
