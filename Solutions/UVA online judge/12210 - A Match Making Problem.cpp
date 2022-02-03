#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3362
int main()
{
    int b,s,T=1;
    while(cin>>b>>s)
    {
        if(b+s==0)break;
        vl c,d;
        int x;
        for(int i=0;i<b;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        sort(ALL(c));
        for(int i=0;i<s;i++)
        {
            cin>>x;
            d.push_back(x);
        }
        cout<<"Case "<<T<<": ";
        if(b>s)
        {
            cout<<b-s<<" "<<c[0]<<"\n";
        }
        else
        {
            cout<<"0\n";
        }
        T++;
    }
}
