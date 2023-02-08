#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/1374

int main()
{
    int n;
    while(cin>>n)
    {
        if(n==0)break;
        int D,M,Y,C;
        vl p1={31,29,31,30,31,30,31,31,30,31,30,31},p2={31,28,31,30,31,30,31,31,30,31,30,31};
        vector<tuple<int,int,int,int> >c;
        for(int i=0;i<n;i++)
        {
            cin>>D>>M>>Y>>C;
            c.push_back(make_tuple(D,M,Y,C));
        }
        ll sum=0,ans=0;
        for(int i=0;i<n-1;i++)
        {
            tie(D,M,Y,C)=c[i];
            if((Y%4==0&&Y%100!=0)||Y%400==0)
            {
                D++;
                if(D==p1[M-1]+1)
                {
                    D=1;
                    M++;
                }
                if(M==13)
                {
                    M=1;
                    Y++;
                }
                if(D==get<0>(c[i+1])&&M==get<1>(c[i+1])&&Y==get<2>(c[i+1]))
                {
                    sum+=get<3>(c[i+1])-get<3>(c[i]);
                    ans++;
                }
            }
            else
            {
                D++;
                if(D==p2[M-1]+1)
                {
                    D=1;
                    M++;
                }
                if(M==13)
                {
                    M=1;
                    Y++;
                }
                if(D==get<0>(c[i+1])&&M==get<1>(c[i+1])&&Y==get<2>(c[i+1]))
                {
                    sum+=get<3>(c[i+1])-get<3>(c[i]);
                    ans++;
                }
            }
        }
        cout<<ans<<" "<<sum<<"\n";
    }

}
