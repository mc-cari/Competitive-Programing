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
 
 //https://atcoder.jp/contests/abc140/tasks/abc140_f
 
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  ll n,x;
  cin>>n;
  ll sec=n;
  n=(1<<n);
  vl c,d;
  multiset<ll> slimes;
  bool o=1;
  for(ll i=0;i<n;i++)
  {
    cin>>x;
    slimes.insert(x);
  }
  c.push_back(*slimes.rbegin());
  slimes.erase(prev(slimes.end()));
  multiset<ll>::iterator it;
  for (int s=0;s<sec;s++)
  {
    //cout<<c.size()<<endl;
    ll prevs=c.size();
    for(int i=0;i<prevs;i++)
    {
        
        it=slimes.lower_bound(c[i]);
        if(it==slimes.begin())
        {
            o=0;
            break;
        }
        c.push_back(*prev(it));
        //cout<<c[i]<<" "<<*prev(it)<<endl;
        slimes.erase(prev(it));
        
    }
    if(!o)break;
 
  }
  
  if(o)cout<<"Yes\n";
  else cout<<"No\n";
}
