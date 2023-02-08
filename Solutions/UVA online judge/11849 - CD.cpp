#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2949
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        if(n+m==0)break;
        int x,sum=0;
        set<int>d;
        while(n--)
        {
            cin>>x;
            d.insert(x);
        }
        while(m--)
        {
            cin>>x;
            if(d.count(x))sum++;
        }
        cout<<sum<<"\n";
    }

}
