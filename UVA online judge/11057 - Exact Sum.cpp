#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=1998&mosmsg=Submission+received+with+ID+24653887
int main()
{

    int n;
    while(cin>>n)
    {
        int x;
        vl c;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        sort(ALL(c));
        int m;
        int ans1,ans2,gap=INF;
        cin>>m;
        for(int i=0;i<n;i++)
        {

            int l=i+1,r=n-1,p,ans=-1;
            while(l<=r)
            {
                p=(l+r)/2;
                if(c[i]+c[p]>=m)
                {
                    if(c[i]+c[p]==m)ans=c[p];
                    r=p-1;
                }
                else l=p+1;
            }
            if(ans!=-1)
            {
                if(ans-c[i]<gap)
                {
                    gap=ans-c[i];
                    ans1=c[i];ans2=ans;
                }
            }

        }
        cout<<"Peter should buy books whose prices are "<<ans1<<" and "<<ans2<<".\n\n";
    }
}
