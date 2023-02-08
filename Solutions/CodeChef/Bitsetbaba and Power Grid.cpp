#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e18
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://www.codechef.com/COOK106A/problems/XORCMPNT

const int N = 1e5 + 10, LOG_A = 31;

ll basis[LOG_A], sz;

// O(N * LOG)
void insertVector(int mask) {
	for (ll i = LOG_A - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
      sz++;
			return;
		}

		mask ^= basis[i];
	}
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    while(t--){
      ll k, m, x;
      cin >> k >> m;
      memset(basis, 0,  sizeof(basis));
      set<ll>c;
      sz = 0;
      for(int i = 0; i < m; i++)
      {
        cin >> x;
        insertVector(x);
      }
      cout << (1 << (k - sz)) << "\n";

    }

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
