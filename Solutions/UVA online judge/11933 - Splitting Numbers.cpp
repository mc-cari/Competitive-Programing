#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3084&mosmsg=Submission+received+with+ID+24585935

int main()
{
    int n;
    while(cin>>n)
    {
        if(n==0)break;
        int a=0,b=0;
        bool o=0;
        for(int i=0;i<=31;i++)
        {
            if(n&(1<<i))
            {
                if(o)
                {
                    b+=(1<<i);
                }
                else
                {
                    a+=(1<<i);
                }
                o=!o;
            }
        }
        cout<<a<<" "<<b<<"\n";
    }
}
