#include <bits/stdc++.h>
using namespace std;
int c;
vector<int>m;
int memo[250][50];
int getWays(int k,int i)
{
    if(i==c)return 0;
    if(k==0)return 1;
    int ans=0;
    if(memo[k][i]!=-1)return memo[k][i];
    if(m[i]<=k)
    {
        ans+=getWays(k-m[i],i);//usar la moneda
    }
    ans+=getWays(k,i+1);//no usar la moneda
    return memo[k][i]=ans;
}
int main()
{

    int n,c,x;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<c;j++)
        {
            memo[i][j]=-1;
        }
    }
    for(int i=0;i<c;i++)
    {
        cin>>x;
        m.push_back(x);
    }
    cout<<getWays(k,0);

    return 0;
}
