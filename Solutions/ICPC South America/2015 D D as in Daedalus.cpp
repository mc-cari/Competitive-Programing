#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/2016
int main()
{
    int n,m,B,x,y,ans=0,ans2=0;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int sum=0,sum2=0;
        cin>>B;
        cin>>x;
        sum+=x;
        for(int j=0;j<n-1;j++)
        {
            cin>>y;
            sum+=y;
            sum2+=y;
        }
        if(sum<=B)
        {
            ans+=x;
        }
        int p=100000;
        for(int j=4;j>=0;j--)
        {
            p/=10;
            if(p+sum2<=B)
            {
                ans2+=p;
                break;
            }
        }
    }
    cout<<ans2-ans<<"\n";
}
