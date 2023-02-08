#include <bits/stdc++.h>
using namespace std;
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=702&page=show_problem&problem=5221
typedef double ll;
typedef vector<ll> vl;
typedef tuple<ll,ll,ll,ll> tll;
typedef pair<ll,ll> pll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m;
    while(cin>>n)
    {
        cin>>m;
        vector<tll >c;
        ll x,y,a,b;
        tll h;
        for(ll i=0;i<m;i++)
        {
            cin>>get<0>(h)>>get<1>(h)>>get<2>(h)>>get<3>(h);
            c.push_back(h);
        }
        int times = 85;
        double l = 0.0;
        double r = 24.0*60;
        double ans,l1,l2, v1, v2;
        while (times--) {
            l1 = (l*2+r)/3;
            l2 = (l+r*2)/3;
            if(1)
            {
                vector<vector<pll> > grafo(n,vector<pll> (0));
                for(int i=0;i<m;i++)
                {
                    tie(x,y,a,b)=c[i];
                    grafo[x-1].push_back(make_pair(a*l1+b,y-1));
                    grafo[y-1].push_back(make_pair(a*l1+b,x-1));
                }
                vector<ll> peso(n,10000000000);
                priority_queue<pll,vector<pll>,greater<pll> >q;
                q.push(make_pair(0,0));

                while(!q.empty()){

                    pll t=q.top();
                    q.pop();
                    ll pes=t.first;
                    int nodo=t.second;
                    for(ll i=0;i<grafo[nodo].size();i++)
                    {
                        if(peso[grafo[nodo][i].second]>pes+grafo[nodo][i].first)
                        {
                            peso[grafo[nodo][i].second]=pes+grafo[nodo][i].first;
                            pll nuevo(pes+grafo[nodo][i].first,grafo[nodo][i].second);
                            q.push(nuevo);
                        }
                    }
                }
                v1=peso[n-1];
            }
            if(1)
            {
                vector<vector<pll> > grafo(n,vector<pll> (0));
                for(int i=0;i<m;i++)
                {
                    tie(x,y,a,b)=c[i];
                    grafo[x-1].push_back(make_pair(a*l2+b,y-1));
                    grafo[y-1].push_back(make_pair(a*l2+b,x-1));
                }
                vector<ll> peso(n,10000000000);
                priority_queue<pll,vector<pll>,greater<pll> >q;
                q.push(make_pair(0,0));

                while(!q.empty()){

                    pll t=q.top();
                    q.pop();
                    ll pes=t.first;
                    int nodo=t.second;
                    for(ll i=0;i<grafo[nodo].size();i++)
                    {
                        if(peso[grafo[nodo][i].second]>pes+grafo[nodo][i].first)
                        {
                            peso[grafo[nodo][i].second]=pes+grafo[nodo][i].first;
                            pll nuevo(pes+grafo[nodo][i].first,grafo[nodo][i].second);
                            q.push(nuevo);
                        }
                    }
                }
                v2=peso[n-1];
            }
            if (v1 > v2)
                r= l2;
            else
                l = l1;
        }
        ans=(v1 + v2) * 0.5;
        cout<<fixed<<setprecision(5)<<ans<<"\n";

    }

    return 0;
}
