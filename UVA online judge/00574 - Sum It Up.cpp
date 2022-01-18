#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=515
int main ()
{
    int n,t;
    while(cin>>t>>n)
    {
        if(n+t==0)break;
        map<vl,bool>p;
        vl c;
        int x;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        sort(c.begin(),c.end());
        vector<vl>sol;
        for(int i=0;i<(1<<n);i++)
        {
            vl d;
            int sum=0;
            for(int j=n-1;j>=0;j--)
            {
                if((i & (1 << j)))
                {
                    d.push_back(c[j]);
                    sum+=c[j];
                }
            }
            if(sum==t)
            {
                if(!p[d]){
                    sol.push_back(d);
                    p[d]=1;
                }
            }
        }
        cout<<"Sums of "<<t<<":\n";
        if(sol.empty())
        {
            cout<<"NONE\n";
        }
        for(int i=sol.size()-1;i>=0;i--)
        {

            for(int j=0;j<sol[i].size();j++)
            {
                cout<<sol[i][j];
                j<sol[i].size()-1? cout<<"+": cout<<"\n";
            }
        }
    }
}
