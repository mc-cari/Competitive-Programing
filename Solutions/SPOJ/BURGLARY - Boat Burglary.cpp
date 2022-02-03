#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }

//https://www.spoj.com/problems/BURGLARY/

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t;
    cin >> t;
    for(int T = 1; T <= t; T++)
    {
      ll n, d, x;
      vl c1, c2;
      cin >> n >> d;
      for(int i = 0; i < n; i++)
      {
        cin >> x;
        if(i <= n/2)c1.push_back(x);
        else c2.push_back(x);
      }
      set<ll> dis;
      if(d == 0)dis.insert(0);
      vector<pll> res1;
      set<pll> res2;
      for(int i = 1; i < (1<<c1.size()); i++)
      {
        ll sum = 0, tam = 0;
        for(int j = 0; j < c1.size(); j++)
        {
          if(i & (1 << j))
          {
            sum += c1[j];
            tam++;
          }
        }
        res1.push_back({sum, tam});
      }
      for(int i = 1; i < (1<<c2.size()); i++)
      {
        ll sum = 0, tam = 0;
        for(int j = 0; j < c2.size(); j++)
        {
          if(i & (1 << j))
          {
            sum += c2[j];
            tam++;
          }
        }
        if(sum == d) dis.insert(tam);
        res2.insert({sum, tam});
      }
      
      for(auto it: res1)
      {
        if(it.first == d)
        {
          dis.insert(it.second);
        }
        if(!res2.empty() && it.first <= d)
        {
          
          auto it1 = res2.lower_bound({d - it.first, 0});
          auto it2 = res2.upper_bound({d - it.first, 1000});
          if(it1 != res2.end() && (*it1).first == d - it.first)
          {
            dis.insert((*it1).second + it.second);
            dis.insert((*prev(it2)).second + it.second);
          }
        }
        
      }
      cout<<"Case #"<<T<<": ";
      if(dis.size() == 0) cout<<"IMPOSSIBLE\n";
      else if(dis.size() > 1) cout<<"AMBIGIOUS\n";
      else cout<<*dis.begin()<<"\n";
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
