#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1444
int n,l,r,m;
bool o;
void back_track(int in,int prev,vector<pll>&c,vl& vis)
{
   if(o)return;
   if(in==n)
   {
       if(prev==l)
       {
           o=1;
       }

       return;
   }

   for(int i=0;i<m;i++)
   {
       if(vis[i])continue;
       if(c[i].first==prev)
       {
           vis[i]=1;
           back_track(in+1,c[i].second,c,vis);
       }
       if(c[i].second==prev)
       {
           vis[i]=1;
           back_track(in+1,c[i].first,c,vis);
       }
       vis[i]=0;
       if(o)return;

   }


}
int main ()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    while(cin>>n)
    {
        if(n==0)break;
        cin>>m;
        int x,y,a,b;
        o=0;
        cin>>x>>y;
        cin>>l>>r;
        vector<pll>c;
        vl vis(m,0);
        for(int i=0;i<m;i++)
        {
            cin>>a>>b;
            c.push_back(make_pair(a,b));
        }
        back_track(0,y,c,vis);
        if(o)cout<<"YES\n";
        else cout<<"NO\n";
    }
}
