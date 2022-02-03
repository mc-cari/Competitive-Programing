#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2077
int main()
{
    int n,k,x;
    while(cin>>n)
    {
        if(n==0)break;
        multiset<int>c;
        multiset<int>::iterator it;
        ll sum=0;
        for(int i=0;i<n;i++)
        {
            cin>>k;
            for (int j=0;j<k;j++)
            {
                cin>>x;
                c.insert(x);
            }
            it=c.begin();
            int a=*it;
            c.erase(it);
            it=prev(c.end());
            int b=*it;
            c.erase(it);
            sum+=b-a;

        }
        cout<<sum<<"\n";

    }

}
