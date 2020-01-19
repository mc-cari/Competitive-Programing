#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/1375
int main()
{
    int n;
    while(cin>>n)
    {
        if(n==0)break;
        vl c(n,-1);
        bool o=0;
        int x,y;
        for(int i=0;i<n;i++)
        {
            cin>>x>>y;
            if(o)continue;
            if(i+y<0||y+i>=n)
            {
                o=1;
                continue;
            }
            if(c[i+y]==-1)
            {
                c[i+y]=x;
            }
            else
            {
                o=1;
                continue;
            }

        }
        if(o)
            cout<<"-1\n";
        else
        {
            for(int i=0;i<n;i++)
            {
                if(i<n-1)cout<<c[i]<<" ";
                else cout<<c[i]<<"\n";
            }
        }
    }
}
