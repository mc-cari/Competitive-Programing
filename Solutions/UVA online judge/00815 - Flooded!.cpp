#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=756

int32_t main() {
    int m,n,t=1;
    while(cin>>m>>n)
    {
      if(m+n==0)break;
      vector<db> c;
      db x,mini=1e9;
      for(int i=0;i<m*n;i++)
      {
        cin>>x;
        mini=min(mini,x);
        c.push_back(x);
      }
      db a;
      cin>>a;
      a/=100.0;
      db l=mini,r=1e7,p,ans=-1,per;
      while(fabs(l-r)>1e-4)
      {
          p=(l+r)/2;
          db cant=0;
          db pe=0;
          for (auto it : c)
          {
            cant+=max(0.0,p-it);
            if(p>it)pe++;
          }
          if(cant<=a){
            l=p;
            ans=p;
            per=pe/(m*n)*100.0;
          }
          else r=p;
      }
      cout<<"Region "<<t<<"\n";
      cout<<fixed<<setprecision(2)<<"Water level is "<<ans<<" meters.\n";
      cout<<per<<" percent of the region is under water.\n\n";
      t++;
    }
    return 0;
}
