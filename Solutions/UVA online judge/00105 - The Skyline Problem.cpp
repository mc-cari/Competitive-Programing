#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))
 

int main() {
  int x, h, y;
  vector<pll>c;
  vl ans;
  multiset<ll>H;
  while(cin>>x>>h>>y)
  {
    c.push_back({x,h});
    c.push_back({y,-h});
  }
  sort(ALL(c));
  H.insert(0);
  bool o=0;
  ll maxi=-1;
  for(int i=0;i<c.size();i++)
  {
    if(c[i].second>0)
    {
      H.insert(c[i].second);
    }
    else
    {
      multiset<ll>::iterator it = H.find(-c[i].second);
      H.erase(H.find(-c[i].second));
    }
    if(i==c.size()-1)
    {
      ans.push_back(c[i].first);
      ans.push_back((*H.rbegin()));
    }
    else if(c[i].first!=c[i+1].first && (ans.empty()||ans.back()!=*H.rbegin()))
    {
      ans.push_back(c[i].first);
      ans.push_back(*H.rbegin());
    }
  }
  for(int i= 0; i < ans.size();i++)
  {
    cout<<ans[i];
    i < ans.size() - 1 ? cout<<" " : cout<<"\n";
  }
  return 0;
}
