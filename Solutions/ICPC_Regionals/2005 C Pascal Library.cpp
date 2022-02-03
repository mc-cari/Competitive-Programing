#include<bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int N ,D,x;
    while(cin>>N>>D)
    {
        if(N+D==0)
        {
            break;
        }
        vector<int>v(N,0);
        for(int i=0;i<D;i++)
        {
            for(int j=0;j<N;j++)
            {
                cin>>x;
                v[j]+=x;
            }
        }
        bool o=0;
        for(int i=0;i<N;i++)
        {
            if(v[i]==D)
                o=1;
        }
        if (o) cout<<"yes\n";
        else cout<<"no\n";
    }
}
