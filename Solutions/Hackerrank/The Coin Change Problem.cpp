#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://www.hackerrank.com/challenges/coin-change/problem
ll memo[251][51];
ll N,M;
ll DP(ll n,ll m,vl& coins)
{

    if(n>N)return 0;
    if(n==N)return 1;
    if(memo[n][m]!=-1)return memo[n][m];
    ll sum=0;
    for(ll i=m;i<M;i++)
    {
        sum+=DP(n+coins[i],i,coins);
    }
    return memo[n][m]=sum;
}
int main()
{
    memset(memo,-1,sizeof(memo));
    ll x;

    cin>>N>>M;
    vl coins;
    for(ll i=0;i<M;i++)
    {
        cin>>x;
        coins.push_back(x);
    }
    cout<<DP(0,0,coins)<<"\n";
}
