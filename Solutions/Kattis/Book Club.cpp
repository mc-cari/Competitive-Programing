#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://open.kattis.com/problems/bookclub

vl match, vis;                                   // global variables
vector<vl> g;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : g[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
  
    g.assign(n, vl());
    match.assign(n, -1);

    for(int i = 0; i < m; i++)
    {
        ll x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }
    

    ll MCBM = 0;
    for(int L = 0; L < n; L++)
    {
        vis.assign(n, 0);
        MCBM += Aug(L);
    }
    if(MCBM == n)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;   

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}