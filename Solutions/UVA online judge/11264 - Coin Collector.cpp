#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2231
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,x;
        cin>>n;
        vl c;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        int sum=0,cont=0,last;
        for(int i=0;i<n-1;i++)
        {
            if(sum+c[i]<c[i+1])
            {

                sum+=c[i];
                cont++;
            }
        }
        if(sum+c[n-1]<2*c[n-1])cont++;
        cout<<cont<<"\n";
    }
}
