#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3344
int main()
{

    int n,m;
    while(cin>>n>>m)
    {
        if(n+m==0)break;
        vector<vl>g(n,vl(m,0));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                int x;
                cin>>x;
                g[i][j]=x;
            }
        }
        int q;
        cin>>q;
        while(q--)
        {
            int L,R,ans=0;
            cin>>L>>R;
            for(int i=0;i<n;i++)
            {
                int l=0,r=m-1,p,lex=-1;
                while(l<=r){

                    p=(l+r)/2;
                    if(g[i][p]>=L)
                    {
                        lex=p;
                        r=p-1;
                    }
                    else l=p+1;
                }
                if(lex==-1)continue;

                for(int j=ans+1;j<=max(m,n);j++)
                {
                    if(i+j-1>=n||lex+j-1>=m)break;
                    if(g[i+j-1][lex+j-1]>R)break;
                    if(j>ans)ans=j;
                }

            }
            cout<<ans<<"\n";
        }
        cout<<"-\n";
    }
}
