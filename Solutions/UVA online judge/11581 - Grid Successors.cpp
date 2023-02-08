#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2628
int main () {
    int t;
    cin>>t;

    while(t--)
    {
        char c[3][3],h[3][3];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>c[i][j];
        int ans=-1;
        bool o=0;
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            if(c[i][j]!='0')o=1;
        }
        while(o)
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    ll sum=0;
                    if(i!=0)sum+=c[i-1][j]-'0';
                    if(j!=0)sum+=c[i][j-1]-'0';
                    if(i!=2)sum+=c[i+1][j]-'0';
                    if(j!=2)sum+=c[i][j+1]-'0';
                    h[i][j]=(char)(sum%2+'0');
                }
            }
            bool o=0;
            for(int i=0;i<3;i++)
            for(int j=0;j<3;j++){
                c[i][j]=h[i][j];
                if(c[i][j]!='0')o=1;
            }
            ans++;
            if(!o)break;
        }
        cout<<ans<<"\n";
    }

    return 0;
}
