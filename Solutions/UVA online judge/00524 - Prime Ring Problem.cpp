#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
int n;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=465
vl prim={2,3,5,7,11,13,17,19,23,29,31,37,41};
bool is_prime(int x)
{
    for(int i=0;i<prim.size();i++)
    {
        if(prim[i]==x)return 1;
    }return 0;
}


void back_track(int in,vl& sol,vl& vis)
{
    if(in==n)
    {
        if(!is_prime(1+sol[in-1]))return;
        for(int i=0;i<n;i++)
        {
            cout<<sol[i];
            i<n-1 ?cout<<" ":cout<<"\n";
        }
    }
    int res=0;
    if(in%2==1)res=1;
    for(int i=1+res;i<=n;i+=2)
    {
        if(vis[i])continue;
        if(!is_prime(i+sol[in-1]))continue;
        sol[in]=i;
        vis[i]=1;
        back_track(in+1,sol,vis);
        sol[in]=0;
        vis[i]=0;
    }

}
int main ()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    while(cin>>n)
    {
        if(t!=1)cout<<"\n";
        vl vis,sol;
        sol.clear();
        sol.assign(22,0);
        vis.clear();
        vis.assign(22,0);
        sol[0]=1;
        vis[1]=1;
        cout<<"Case "<<t<<":\n";
        t++;
        back_track(1,sol,vis);
    }
}
