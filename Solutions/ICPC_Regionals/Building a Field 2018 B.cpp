#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

https://www.urionlinejudge.com.br/judge/es/problems/view/2904

int32_t main()
{
    int n,x,sum=0,ans=0;
    cin>>n;
    vl c,d;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        sum+=x;
        c.push_back(x);
        d.push_back(sum);
    }
    if(sum%2==1)
    {
        cout<<"N\n";
        return 0;
    }
    int l=0,r=1;
    while(r<n-1)
    {
        while(r<n-1&&(d[r]-d[l]+c[l])<sum/2)
        {
            r++;
        }
        if(r==n-1)break;
        if(d[r]-d[l]+c[l]==sum/2)ans++;

        l++;
    }
    if(ans>1)
    {
        cout<<"Y\n";
    }
    else cout<<"N\n";

}
