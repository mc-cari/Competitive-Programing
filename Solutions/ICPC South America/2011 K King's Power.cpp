#include<bits/stdc++.h>
using namespace std;
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3810
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int a,b,c,x,y;
    while(cin>>a>>b>>c)
    {
        if(a+b+c==0)break;
        if(a==b&&b==c)
        {
            if(a==13)cout<<"*\n";
            else cout<<a+1<<" "<<a+1<<" "<<a+1<<"\n";
        }
        else if(a!=b && b!=c && c!=a)
        {
            cout<<"1 1 2\n";
        }
        else
        {
            vl A={a,b,c};
            sort(A.begin(),A.end());
            int p=0,n=0;
            if(A[0]==A[1])
            {
                p=A[0];n=A[2];
            }
            else
            {
                p=A[2];n=A[0];
            }
            if(n!=13)
            {
                if(p!=n+1)
                {
                    if(p<n+1)
                    cout<<p<<" "<<p<<" "<<n+1<<"\n";
                    else
                        cout<<n+1<<" "<<p<<" "<<p<<"\n";
                }

                else
                {
                    if(n==12&&p==13)
                        cout<<"1 1 1\n";
                    else cout<<p<<" "<<p<<" "<<n+2<<"\n";
                }
            }
            else cout<<"1 "<<p+1<<" "<<p+1<<"\n";
        }
    }
	return 0;
}
