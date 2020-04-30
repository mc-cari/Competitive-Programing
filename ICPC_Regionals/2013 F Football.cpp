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

//https://www.urionlinejudge.com.br/judge/es/problems/view/1495

int main()
{
  int n,g;
  while(cin>>n>>g)
  {
    ll points=0,x,y;
    vector<tuple<ll,ll,ll> >c;
    for(int i=0;i<n;i++)
    {
      cin>>x>>y;
      if(x>y)
      {
        points+=3;
      }
      else
      {
        c.push_back(make_tuple(y-x+1,x,y));
      }
      
    }
    sort(ALL(c));
    for(int i=0;i<c.size();i++)
    {
      if(g>=get<0>(c[i]))
      {
        g-=get<0>(c[i]);
        get<0>(c[i])=0;

      }
      else
      {
        ll aux=g;
        get<0>(c[i])-=g;
        g=0;
      }
      if(get<0>(c[i])==0)
      {
        points+=3;
      }
      else if(get<0>(c[i])==1)
      {
        points+=1;
      }
      
    }
    cout<<points<<"\n";
  }
}
