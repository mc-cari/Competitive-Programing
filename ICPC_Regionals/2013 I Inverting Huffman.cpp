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

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
  int n;
  while(cin >> n)
  {
    ll maxi = 1, x, ans = 0;
    vector<vl>levels(51, vl(0));
    vector<ll>nodes(51, 0);
    for(int i = 0; i < n; i++)
    {
      cin >> x;
      nodes[x]++;
    }
    for(int i = 50; i >= 1; i--)
    {
      for(int j = 0; j < nodes[i]; j++)
      {
        ans += maxi;
        levels[i].push_back(maxi);
      }
      sort(ALL(levels[i]));
      for(int j = 0; j < levels[i].size(); j += 2)
      {
        maxi = max(maxi, max(levels[i][j], levels[i][j+1]));
        levels[i-1].push_back(levels[i][j] + levels[i][j+1]);
      }
    }
    cout<<ans<<"\n";
  }
  
    
  return 0;
}

