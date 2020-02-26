#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1836
int main() {

    int m,n,in,x;
    while(cin>>m>>n)
    {
        vector<vector<pll> >c(n,vector<pll>(0));
        for(int k=0;k<m;k++)
        {
            cin>>in;
            vector<pll>d;
            for(int i=0;i<in;i++)
            {
                cin>>x;
                d.push_back(make_pair(x,0));
            }
            for(int i=0; i<in;i++)
            {
                cin>>x;
                d[i].second=x;
            }
            for(int i=0;i<in;i++)
            {
                c[d[i].first-1].push_back(make_pair(k+1,d[i].second));
            }
        }
        cout<<n<<" "<<m<<"\n";
        for(int i=0;i<n;i++)
        {
            if(c[i].size()==0)
            {
                cout<<"0\n\n";
                continue;
            }

            cout<<c[i].size()<<" ";
            for(int j=0;j<c[i].size();j++)
            {
                cout<<c[i][j].first;
                j<c[i].size()-1 ? cout<<" " : cout<<"\n";
            }
            for(int j=0;j<c[i].size();j++)
            {
                cout<<c[i][j].second;
                j<c[i].size()-1 ? cout<<" " : cout<<"\n";
            }
        }
    }


}
