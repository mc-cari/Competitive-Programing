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

//https://open.kattis.com/problems/skilifts

int main() {
    
    ll n, x, y, a;
    ll ans = 0;
    cin >> n;
    vector<pll>col;
    for(int i = 0; i<=1e5; i++)
    {
        col.push_back({0,0});
    }

    for(int i = 0; i < n; i++)
    {
      cin >> x >> y >> a;
      col[y].first++;
      if(a==2)col[y].second++;
    }
    for(int i = 0; i <= 1e5; i++)
    {
        ll sum = min(col[i].first, col[i+1].first);
        ans += sum;
        col[i+1].first -= max(0LL, sum - col[i+1].second);
    }

    cout<<ans<<"\n";


    return 0;
}
