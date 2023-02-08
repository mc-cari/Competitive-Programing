#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://acm.timus.ru/status.aspx?space=1
vector<pll> c;
ll n;
ll memo[501][501];
ll DP(int i,int h)
{
    if(i<=0)return 1;
    if(memo[i][h]!=-1)return memo[i][h];
    ll in=i,sum=0;
    while(in>h)
    {
        sum+=DP(i-in,in);
        in--;
    }
    return memo[i][h]=sum;
}

int main()
{
    memset(memo,-1,sizeof(memo));
    cin>>n;
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        if(n-i>i)
            sum+=DP(n-i,i);
    }
    cout<<sum<<"\n";

}
