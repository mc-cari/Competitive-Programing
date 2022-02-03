#include<bits/stdc++.h>
using namespace std;
typedef double ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/2905
vector<pll> c;
ll n;
double memo[10010][122][7];
double DP(int i,int t,int d)
{
    if(t>=120)t=0;
    if(d==7)t=0;
    //cout<<i<<" "<<t<<" "<<d<<endl;
    if(i==n)
    {
        return 0;
    }
    if(memo[i][t][d]!=-1)
    {
        return memo[i][t][d];
    }
    ll mini=INF;
    if(t==0)
    {
        mini=min(mini,c[i].second+DP(i+1,c[i].first,2));
        mini=min(mini,c[i].second+DP(i+1,0,0));
    }
    else
    {
        if(d==2)
        {
            mini=min(mini,c[i].second*0.5+DP(i+1,c[i].first+t,d+1));
        }
        else
        {
            mini=min(mini,c[i].second*0.25+DP(i+1,c[i].first+t,d+1));
        }
        if(d==2)
        {
            mini=min(mini,c[i].second*0.5+DP(i+1,0,0));
        }
        else
        {
            mini=min(mini,c[i].second*0.25+DP(i+1,0,0));
        }
    }
    return memo[i][t][d]=mini;
}

int main()
{
    for(int i=0;i<10010;i++)
    {
        for(int j=0;j<122;j++)
        {
            for(int z=0;z<7;z++)
            {
                memo[i][j][z]=-1;
            }
        }
    }
    cin>>n;
    ll x,y;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        c.push_back(make_pair(x,y));
    }
    cout<<fixed<<setprecision(2)<<DP(0,0,0)<<"\n";
}
