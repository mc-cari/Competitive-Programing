#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

// use less_equal for multiset
template <typename T, typename Comparator = less<T>>
using ordered_set = tree<T, null_type, Comparator, rb_tree_tag,
                         tree_order_statistics_node_update>;
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

 
// order_of_key(T x)
// -> returns the number of elements strictly smaller than x

// find_by_order(size_t i) 
// -> returns iterator to i-th largest element (counting from 0)

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
  int t;
  cin >> t;
  while(t--)
  {
    int n, k, x, y;
    ordered_set<int> m;
    vector<pll> c;
    cin >> n >> k;
    for(int i = 0; i < n; i ++)
    {
      cin >> x >> y;
      c.push_back({x, y});
    }
    sort(ALL(c));
    ll ans = 0;
    for(int i = 0; i < n; i++)
    {
      ll num =m.order_of_key(c[i].second + 1);
      if(abs(num - (n-1 - num)) >= k)ans++;
      m.insert(c[i].second);
    }
    cout<<ans<<"\n";
  }
  
    
  return 0;
}
