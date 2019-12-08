#include<bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int n,x;
    while(cin>>n)
    {
        if(n==0)break;
        vl c;
        int in=-1;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(x==1)
                in=i;
            c.push_back(x);
        }
        if(in==-1)
        {
            cout<<(n+1)/2<<"\n";
        }
        else
        {
            ll sum=0,s=0;
            for(int i=0;i<n;i++)
            {
                if(c[in]==0)
                {
                    sum++;
                }
                else
                {
                    s+=sum/2;
                    sum=0;
                }
                in++;
                if(in==n)in=0;
            }
            s+=sum/2;
            cout<<s<<"\n";
        }
    }
}
