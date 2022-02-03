#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1043
int main()
{
    int n;
    while(cin>>n)
    {
        char c[n][n];
        int maxi=-1;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>c[i][j];


        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            {
                int mini=INF;
                if(c[i][j]=='1')
                {
                    for(int a=0;a<n;a++)
                        for(int b=0;b<n;b++)
                        {
                            if(c[a][b]=='3')mini=min(mini,abs(a-i)+abs(b-j));
                        }
                    maxi=max(maxi,mini);
                }

            }
        cout<<maxi<<"\n";
    }


}
