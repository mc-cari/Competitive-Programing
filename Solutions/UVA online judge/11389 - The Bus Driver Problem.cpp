#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2384
int main()
{
    int n,D,r;
    while(cin>>n>>D>>r)
    {
        if(n+D+r==0)break;
        vl c,d;
        int x;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        for(int i=0;i<n;i++)
        {
            cin>>x;
            d.push_back(x);
        }
        sort(ALL(c));
        sort(d.rbegin(),d.rend());
        int sum=0;
        for(int i=0;i<n;i++)
        {
            if(c[i]+d[i]>D)
                sum+=(c[i]+d[i]-D)*r;
        }
        cout<<sum<<"\n";
    }
}
