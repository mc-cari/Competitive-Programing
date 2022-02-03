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
#define PI acos(-1.0) 

//https://atcoder.jp/contests/agc043/tasks/agc043_b

int main()
{
  int n;
  string s;
  cin>>n>>s;
  vl c,d;
  bool o=0;
  for(int i=0;i<n;i++)
  {
    c.push_back((s[i]-'0')-1);
    if(c[i]==1)o=1;

  }

  for(int i=0;i<n;i++)
  {
    if(c[i]==2)
    {
      if(!o)c[i]=1;
      else c[i]=0;
    }
  }
  while(c.size()!=1)
  {
    int maxlog = 31 - __builtin_clz(c.size());
    ll des = 1<<maxlog;
    if(des==c.size())des=des>>1;
    for(int i=0;i<c.size()-des;i++)
    {
      d.push_back(c[i]^c[i+des]);
    }
    c.clear();
    c.assign(ALL(d));
    d.clear();
  }
  if(c[0]==1)
  {
    if(o)cout<<c[0];
    else cout<<2<<endl;
  }
  else
  cout<<c[0]<<"\n";
}
