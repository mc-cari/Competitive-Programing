#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=6211

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
  string n;
  while(cin >> n)
  {
    deque<ll> v;
    ll p = n.size();
    for(int i = n.size() -1; i >= 0; i--)
    {
      if(n[i] == 'a' || n[i] == 'e' || n[i] == 'i' || n[i] == 'o' || n[i] == 'u')
      {
        v.push_front(p - i);
        p = i;
      }
    }
    if(!(n[0] == 'a' || n[0] == 'e' || n[0] == 'i' || n[0] == 'o' || n[0] == 'u') && !v.empty())
    {
      cout<<"0\n";
      continue;
    }
    if(v.empty())
    {
      cout<<"1\n";
      continue;
    }
    cout<<v[v.size() - v.size()/2 - 1]<<"\n";
  }
  
    
  return 0;
}

