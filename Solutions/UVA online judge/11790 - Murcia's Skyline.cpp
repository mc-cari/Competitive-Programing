#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2890
vl A,p;

int main()
{
    ll t,n;
    cin>>t;
    for(int T=1;T<=t;T++)
    {
        A.clear();
        int x,y;
        vl W;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            A.push_back(x);
        }
        for(int i=0;i<n;i++)
        {
            cin>>x;
            W.push_back(x);
        }
        vl L(n, 0), L2(n,0);
        ll in=0,dec=0;
        for(int i=0;i<n;i++)
        {
            L[i]=W[i];
            L2[i]=W[i];
            for(int j=0;j<i;j++)
            {
                if(A[j]>A[i])
                {
                    L[i]=max(L[i],L[j]+W[i]);
                }
                if(A[j]<A[i])
                {
                    L2[i]=max(L2[i],L2[j]+W[i]);
                }
            }
            in=max(in,L2[i]);
            dec=max(dec,L[i]);

        }
        cout<<"Case "<<T<<". ";
        if(in>=dec)
        {
            cout<<"Increasing ("<<in<<"). Decreasing ("<<dec<<").\n";
        }
        else
            cout<<"Decreasing ("<<dec<<"). Increasing ("<<in<<").\n";

    }

    return 0;
}
