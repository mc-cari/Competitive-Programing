#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://www.urionlinejudge.com.br/judge/es/problems/view/1431
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k,x;
    while(cin>>n)
    {
        if(n==0)break;
        vector<vl>g(n,vl(0));
        for(int i=0;i<n;i++)
        {
            cin>>k;
            for(int j=0;j<k;j++)
            {
                cin>>x;
                g[i].push_back(x);
            }
            sort(g[i].begin(),g[i].end());
        }
        ll sum=INF;
        for(int t=0;t<=1000;t++)
        {
            ll tmp=0;
            for(int i=0;i<n;i++)
            {
                if(g[i].size()==1)
                {
                    tmp++;
                    continue;
                }
                int l=0,r=g[i].size()-1,p;
                while(l<=r)
                {
                    p=(l+r)/2;
                    //cout<<p<<endl;
                    if(g[i][p]<=t)l=p+1;
                    else r=p-1;
                }
                l=r+1;
                if(l>=g[i].size()||g[i][l]<t)
                {
                    tmp+=g[i].size();
                }
                else
                {
                    ll a=l;
                    ll b=g[i].size()-a;
                    tmp+=abs(a-b);
                }
            }
            if(tmp<sum)sum=tmp;
        }
        cout<<sum<<"\n";

    }
}
