#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3142
int main() {

    int n,m,x,k;
    while(cin>>n>>m)
    {
        map<int,vector<int> >c;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c[x].push_back(i+1);
        }
        for(int i=0;i<m;i++)
        {
            cin>>k>>x;
            if(k>c[x].size())
            {
                cout<<"0\n";
            }
            else cout<<c[x][k-1]<<"\n";
        }
    }


}
