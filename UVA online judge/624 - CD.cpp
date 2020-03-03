#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
vl ans;
int n,maxi;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=565
void back_track(int in,int sum,vl& vis, vl& c)
{
    if(sum>maxi)
    {
        maxi=sum;
        ans.clear();
        ans.assign(ALL(vis));


    }
    for(int i=in;i<c.size();i++)
    {
        if(sum+c[i]>n)continue;
        vis.push_back(c[i]);
        back_track(i+1,sum+c[i],vis,c);
        vis.pop_back();
    }
}
int main()
{

    int t;
    while(cin>>n>>t)
    {
        vl c;
        int x;
        for(int i=0;i<t;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        maxi=0;
        vl vis;
        back_track(0,0,vis,c);
        for(int i=0;i<ans.size();i++)
        {
            cout<<ans[i]<<" ";
        }cout<<"sum:"<<maxi<<"\n";
    }
}
