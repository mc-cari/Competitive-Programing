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

// From https://github.com/stevenhalim/cpbook-code/blob/master/ch4/mcbm.cpp


vl match, vis;                                   // global variables
vector<vl> g;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto it : g[L])
    if ((match[it] == -1) || Aug(match[it])) {
      match[it] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll V, Vleft;
    match.assign(V, -1);
    ll MCBM = 0;
    for(int L = 0; L < Vleft; L++)
    {
        vis.assign(Vleft, 0);
        MCBM += Aug(L);
    }
    cout << "Found " << MCBM << " matchings\n";    // the answer is 2 for Figure 4.38
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}