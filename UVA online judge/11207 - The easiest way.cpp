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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2148

db size(db h,db w)
{
  int op1,op2=0,op3=0;
  op1=(min(h,w)/2*min(h,w)/2);
  if(min(h,w)*4<=max(h,w))
    op2=min(h,w)*min(h,w);
  if(max(h,w)/4<=min(h,w))
    op3=max(h,w)/4*max(h,w)/4;
  return max(op1,max(op2,op3));
}
int32_t main() {
    db n;
    while(cin>>n)
    {
      if(n==0)break;
      db maxi=-1,in,h,w;
      for(int i=1;i<=n;i++)
      {
        cin>>h>>w;
        if(size(h,w)>maxi)
        {
          maxi=size(h,w);
          in=i;
        }
      }
      cout<<in<<"\n";
    }
    return 0;
}
