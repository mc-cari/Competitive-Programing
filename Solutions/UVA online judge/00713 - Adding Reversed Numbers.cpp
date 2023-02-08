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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=654

int main()
{
  int t;
  cin>>t;
  while(t--)
  {

    string a,b;
    cin>>a>>b;
    if(b.size()<a.size())swap(a,b);
    vector<int>c;
    for(int i=a.size();i<b.size();i++)
    {
      a+="0";
    }
    int carry=0;
    for(int i=0;i<a.size();i++)
    {
      c.push_back((a[i]-'0'+b[i]-'0'+carry)%10);
      carry=(a[i]-'0'+b[i]-'0'+carry)/10;
    }
    if(carry!=0)c.push_back(carry);
    bool o=1;
    for(auto it : c)
    {
      if(o&&it==0)continue;
      o=0;
      cout<<it;
    }cout<<"\n";

  }
}
