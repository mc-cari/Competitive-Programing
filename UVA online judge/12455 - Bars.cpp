#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3886
int main() {

    int t;
    cin>>t;
    while(t--)
    {
        int n,p,x;
        cin>>n>>p;
        vl c;
        for(int i=0;i<p;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        bool o=0;
        if(n==0)o=1;
        for(int i=1;i<(1<<p);i++)
        {
            int sum=0;
            for(int j=0;j<p;j++)
            {
                if((i & (1 << j)))
                {
                    sum+=c[j];
                }
            }
            if(sum==n)o=1;
        }
        if(o)cout<<"YES\n";
        else cout<<"NO\n";
    }
}
