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

//https://www.urionlinejudge.com.br/judge/es/problems/view/2351
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  ll n,k,x;
  ll sum=0;
  cin>>n>>k;
  vl c;
  multiset<ll>d;
  for(ll i=0;i<n;i++)
  {
    cin>>x;
    sum+=x;
    c.push_back(x);
  }
  ll cont=0,p=0;
  for(ll i=0;i<n;i++)
  {
    cont++;
    if(cont==k+1)
    {
      cont=0;
      p++;
    }
    d.insert(c[i]);
    while(d.size()>p)
    {
      d.erase(d.begin());
    }
    
    
    
  }
  for(auto it : d)
  {
    sum-=it;
  }
  cout<<sum<<"\n";
}
