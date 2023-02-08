#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

//https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14/problem
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e18
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

vl c;
vl ac;

ll cost(ll i, ll j)
{
  return (j - i + 1) * (ac[j+1] - ac[i]);
}

vector<ll> last, now;

void compute(int l, int r, int optl, int optr)
{
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<ll, int> best = {cost(0, mid), -1};

    for(int k = max(1, optl); k < min(mid, optr) + 1; k++)
        best = min(best, {last[k - 1] + cost(k, mid), k});

    now[mid] = best.first;

    compute(l, mid - 1, optl, best.second);
    compute(mid + 1, r, best.second, optr);
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

    
  ll l, g, x, w;
  while(cin >> l >> g){
    
    c.clear();
    for(int i = 0; i < l; i++){

      cin >> x;
      c.push_back(x);
    }

    ac.clear();
    ac.push_back(0);

    for(int i = 0; i < l; i++){
      ac.push_back(c[i]);
      ac.back() += ac[i];
    }

    last.assign(l, INF);
    now.resize(l);

    for(int i = 0; i < g; i++) { compute(0, l - 1, 0, l - 1); swap(last, now); }

    cout<< last[l-1]<<"\n";

  }




  
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
