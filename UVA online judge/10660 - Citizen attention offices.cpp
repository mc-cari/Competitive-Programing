#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1601
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,x,y,z,a1,a2,a3,a4,a5;
        cin>>n;
        int C[25][25];
        memset(C,0,sizeof(C));
        while(n--)
        {
            cin>>x>>y>>z;
            C[x][y]=z;
        }
        int mini=INF;
        for(int a=0;a<25;a++)
        {
            for(int b=a+1;b<25;b++)
            {
                for(int c=b+1;c<25;c++)
                {
                    for(int d=c+1;d<25;d++)
                    {
                        for(int f=d+1;f<25;f++)
                        {
                            int sum=0;
                            for(int i=0;i<25;i++)
                            {
                                int minit=INF;
                                minit=min(minit,(abs(a%5-i%5)+abs(a/5-i/5))*C[i/5][i%5]);
                                minit=min(minit,(abs(b%5-i%5)+abs(b/5-i/5))*C[i/5][i%5]);
                                minit=min(minit,(abs(c%5-i%5)+abs(c/5-i/5))*C[i/5][i%5]);
                                minit=min(minit,(abs(d%5-i%5)+abs(d/5-i/5))*C[i/5][i%5]);
                                minit=min(minit,(abs(f%5-i%5)+abs(f/5-i/5))*C[i/5][i%5]);
                                sum+=minit;
                            }
                            if(sum<mini)
                            {
                                mini=sum;
                                a1=a;a2=b;a3=c;a4=d;a5=f;
                            }
                        }
                    }
                }
            }

        }
        cout<<a1<<" "<<a2<<" "<<a3<<" "<<a4<<" "<<a5<<"\n";

    }


}
