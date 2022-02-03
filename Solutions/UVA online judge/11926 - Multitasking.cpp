#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3077&mosmsg=Submission+received+with+ID+24585725

int main()
{
    int n,m,x,y,z;
    while(cin>>n>>m)
    {
        if(n+m==0)break;
        bitset<1000002> a,b;
        bool o=0;
        while(n--)
        {
            cin>>x>>y;
            if(a[x]==1)
            {
                o=1;
            }
            a.set(x);
            b.set(y);
        }
        while(m--)
        {
            cin>>x>>y>>z;
            int in=0;
            while(z*in+x<=1000000)
            {
                if(a[x+z*in]==1)
                {
                    o=1;break;
                }
                a.set(x+z*in);
                if(y+z*in<=1000000)
                    b.set(y+z*in);
                in++;
            }
        }
        if(o)
        {
            cout<<"CONFLICT\n";
            continue;
        }
        int in=0;
        for(int i=0;i<=1000000;i++)
        {
            in+=a[i];
            in-=b[i];
            if(in>1)
            {
                o=1;
                break;
            }
        }
        if(o)cout<<"CONFLICT\n";
        else cout<<"NO CONFLICT\n";
    }
}
