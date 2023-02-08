#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1597
int main()
{
    int n;
    while(cin>>n)
    {
        if(n==0)break;
        vl sol;
        int x,sum=0;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            sum+=x;
            if(x>0)sol.push_back(x);
        }
        for(int i=0;i<sol.size();i++)
        {
            cout<<sol[i];
            i<sol.size()-1 ? cout<<" ":cout<<"\n";
        }
        if(sum==0)cout<<"0\n";
    }
}
