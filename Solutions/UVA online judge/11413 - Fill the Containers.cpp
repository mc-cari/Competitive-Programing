#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2408
int main()
{
    int n,m;
    while(cin>>n>>m){
        int x,sum=0,maxi=-1;;
        vl c;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            sum+=x;
            maxi=max(maxi,x);
            c.push_back(x);
        }
        int l=maxi,r=sum,p,ans=-1;
        while(l<=r)
        {
            p=(l+r)/2;
            int vessel=1,acum=0;
            for(int i=0;i<n;i++)
            {
                if(acum+c[i]>p)
                {
                    vessel++;
                    acum=c[i];
                }
                else
                {
                    acum+=c[i];
                }
            }
            if(vessel<=m)
            {
                r=p-1;
                ans=p;
            }
            else
            {
                l=p+1;
            }

        }
        cout<<ans<<"\n";
    }
}
