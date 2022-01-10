#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/1418
int n,t;
int minimal(int x,vector<vl>& grafo)
{
    if(grafo[x].size()==0)
    {
        return 1;
    }
    vl c;
    for(int i=0;i<grafo[x].size();i++)
    {
        c.push_back(minimal(grafo[x][i],grafo));
    }
    sort(c.begin(),c.end());
    double y=grafo[x].size()*(t/100.0);
    int Y=ceil(y);
    ll sum=0;
    for(int i=0;i<Y;i++)
    {
        sum+=c[i];
    }
    return sum;
}
int main()
{

    while(cin>>n>>t)
    {
        int x;
        if(n+t==0)break;
        vector<vl> grafo(n+1,vl(0));
        for(int i=0;i<n;i++)
        {
            cin>>x;
            grafo[x].push_back(i+1);
        }
        cout<<minimal(0,grafo)<<"\n";


    }
}
