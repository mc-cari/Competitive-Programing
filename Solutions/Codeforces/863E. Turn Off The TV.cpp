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

//https://codeforces.com/problemset/problem/863/E

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll n,x,y;
  cin>>n;
  set<int>imp,sweep;
  vector<tuple<ll,ll,ll>>c;
  for(int i=0;i<n;i++)
  {
    cin>>x>>y;
    if(x==y)
    {
      c.push_back(make_tuple(x,1,i));
    }
    else{
      c.push_back(make_tuple(x,0,i));
      c.push_back(make_tuple(y,2,i));
    }

  }
  sort(ALL(c));
  for(int i=0;i<c.size();i++)
  {
    if(get<1>(c[i])==0)
    {
      sweep.insert(get<2>(c[i]));
    }
    else if(get<1>(c[i])==1)
    {
      if(sweep.size()==0)
      {
        imp.insert(get<2>(c[i]));
      }
      continue;
    }
    else
    {
      sweep.erase(get<2>(c[i]));
    }
    //cout<<sweep.size()<<" "<<i<<endl;
    if(i==c.size()-1||get<0>(c[i])!=get<0>(c[i+1]))
    {

      if(sweep.size()==1)
      {
        if(i==c.size()-1)
          imp.insert(*sweep.begin());
        else if(get<1>(c[i])==2)
        {
          if(get<0>(c[i+1])==get<0>(c[i])+1&&get<1>(c[i+1])==2)
            imp.insert(*sweep.begin());
          else if(get<0>(c[i+1])!=get<0>(c[i])+1)
            imp.insert(*sweep.begin());
        }
        else if(get<1>(c[i])==0)
          imp.insert(*sweep.begin());
      }
    }
  }
  for(int i=0;i<n;i++)
  {
    if(!imp.count(i))
    {
      cout<<i+1<<"\n";
      return 0;
    }
  }
  cout<<"-1\n";
}
