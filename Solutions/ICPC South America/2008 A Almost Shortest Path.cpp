#include<bits/stdc++.h>
//https://www.spoj.com/problems/SAMER08A/
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
ll inicio,destino;
pll z;
 
 
int main()
{
 
	ll v,x,y,e,B,P;
	pll h;
	while(cin>>v>>e){
		if(v+e==0)break;
		cin>>destino>>inicio;
		vector<vector<pll> > grafo(v,vector<pll> (0));
		vector<vector<pll> > grafo2(v,vector<pll> (0));
		vector<ll> peso(v,(ll)INF);
		vl llegue(v,(ll)INF);

		ll weight;
		for(ll i=0;i<e;i++)
		{
			cin>>x>>y>>weight;
			h.first=weight;
			h.second=x;
			grafo[y].push_back(h);
			h.second=y;
			grafo2[x].push_back(h);
		}


		priority_queue<pll,vector<pll>,greater<pll> >q;//comandos para ordenar de menor a mayor

		pll inicial(0,inicio);
		llegue[inicio]=0;

		q.push(inicial);
		peso[inicio]=0;
		while(!q.empty()){

			pll t=q.top();
		    q.pop();
			ll pes=t.first;
			ll nodo=t.second;
			for(ll i=0;i<grafo[nodo].size();i++)
			{

				if(peso[grafo[nodo][i].second]>pes+grafo[nodo][i].first)
				{
					peso[grafo[nodo][i].second]=pes+grafo[nodo][i].first;
					pll nuevo(pes+grafo[nodo][i].first,grafo[nodo][i].second);
					q.push(nuevo);
					llegue[grafo[nodo][i].second]=nodo;
				}
		    }
		}
		int maxi=peso[destino];
		//cout<<maxi<<endl;
		vl peso2;

		for(ll i=0;i<v;i++)
		{
			peso2.push_back(peso[i]);
		}

		peso.clear();

		peso.assign(v,(ll)INF);

		inicial.first=0;
		inicial.second=destino;
		q.push(inicial);
		peso[destino]=0;
		while(!q.empty()){

			pll t=q.top();
		    q.pop();
			ll pes=t.first;
			ll nodo=t.second;
			for(ll i=0;i<grafo2[nodo].size();i++)
			{

				if(peso[grafo2[nodo][i].second]>pes+grafo2[nodo][i].first)
				{
					peso[grafo2[nodo][i].second]=pes+grafo2[nodo][i].first;
					pll nuevo(pes+grafo2[nodo][i].first,grafo2[nodo][i].second);
					q.push(nuevo);
				}
		    }
		}
		//cout<<peso[inicio]<<endl;
		vl peso3;
		for(ll i=0;i<v;i++)
		{
			peso3.push_back(peso[i]);
		}

		peso.clear();
		peso.assign(v,(ll)INF);
		inicial.first=0;
		inicial.second=destino;
		q.push(inicial);
		peso[destino]=0;
		while(!q.empty()){

			pll t=q.top();
			q.pop();
			ll pes=t.first;
			ll nodo=t.second;
			for(ll i=0;i<grafo2[nodo].size();i++)
			{
			    //cout<<nodo<<" "<<grafo2[nodo][i].second<<" "<<peso3[nodo]<<" "<<grafo2[nodo][i].first<<" "<<peso2[grafo2[nodo][i].second]<<endl;
				if(peso3[nodo]+grafo2[nodo][i].first+peso2[grafo2[nodo][i].second]==maxi)continue;
				if(peso[grafo2[nodo][i].second]>pes+grafo2[nodo][i].first)
				{
					peso[grafo2[nodo][i].second]=pes+grafo2[nodo][i].first;
					pll nuevo(pes+grafo2[nodo][i].first,grafo2[nodo][i].second);
					q.push(nuevo);
				}
		    }
		}
		if(peso[inicio]==INF)cout<<"-1\n";
		else cout<<peso[inicio]<<endl;
	}
	return 0;
}
 
