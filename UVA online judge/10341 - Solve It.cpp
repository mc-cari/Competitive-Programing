#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1282
int main()
{
    int w,q,r,s,t,u;
    while(cin>>w>>q>>r>>s>>t>>u)
    {
        double l=0.0,R=1.0,p,ans=-1;

        for(int j=0;j<100;j++)
        {
            p=(l+R)/2;
            double res=w*exp(-p)+q*sin(p)+r*cos(p)+s*tan(p)+t*p*p+u;
            if(res>0.0)
            {
                l=p;
            }
            else{
                R=p;
                if(abs(res-0)<0.00001)ans=p;
            }
        }
        if(ans==-1)
        {
            cout<<"No solution\n";
        }
        else cout<<fixed<<setprecision(4)<<ans<<"\n";


    }

}
