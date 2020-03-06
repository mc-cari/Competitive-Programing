#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2098
int main()
{
    int t;
    cin>>t;
    for(int T=1;T<=t;T++)
    {
        ll N,D;
        cin>>N>>D;
        vector<string>c;
        string x;

        for(int i=0;i<N;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        ll prev=0,maxi=0;
        vl vis(N,0);
        for(int i=0;i<N;i++)
        {
            ll dist=stoll(c[i].substr(2,c[i].length()-2));
            maxi=max(maxi,dist-prev);
            prev=dist;
            if(c[i][0]=='S')
            {
                vis[i]=1;
                if(i<N-1&&c[i+1][0]=='S')i++;
            }
        }
        maxi=max(maxi,D-prev);
        prev=D;
        for(int i=N-1;i>=0;i--)
        {
            if(vis[i])continue;
            ll dist=stoll(c[i].substr(2,c[i].length()-2));
            maxi=max(maxi,prev-dist);
            prev=dist;
        }
        maxi=max(maxi,prev);
        cout<<"Case "<<T<<": "<<maxi<<"\n";
    }
}
