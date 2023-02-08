#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2177
int main()
{
    for(int a=1;a*4<=2000;a+=1)
    {
        for(int b=a;a+b*3<=2000;b+=1)
        {
            for(int c=b;a+b+c*2<=2000;c+=1)
            {
                long long x=a+b+c,y=(ll)a*b*c;
                if(y>1000000&&(x*1000000)%(y-1000000)==0)
                {
                    int d=(x*1000000)/(y-1000000);
                    x+=d;
                    if(d<c||x>2000)continue;
                    cout<<fixed<<setprecision(2)<<a/100.0<<" "<<b/100.0<<" "<<c/100.0<<" "<<d/100.0<<"\n";
                }

            }
        }

    }
}
