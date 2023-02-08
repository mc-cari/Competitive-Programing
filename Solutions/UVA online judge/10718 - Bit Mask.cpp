#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1659
int main()
{
    ll n,l,u;
    while(cin>>n>>l>>u)
    {
        ll m=0;

        for( ll i=31;i>=0;i--)
        {
            if((n & (1LL << i)))
            {

                if(m+(1LL<<i) <=l)m+=(1LL<<i);
            }
            else
            {
                if(m+(1LL<<i)<=u)m+=(1LL<<i);
            }
        }
        cout<<m<<"\n";
    }
}
