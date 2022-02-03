#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/contest/813/problem/E

typedef vector<int>::iterator iter;

//Wavelet tree with succinct representation of bitmaps
struct WaveTreeSucc {
  vector<vector<int> > C; int s;

  // sigma = size of the alphabet, ie., one more than the maximum element
  // in S.
  // si no  esta indexado desde 0, agregar mas tamaño(sigma)
  WaveTreeSucc(vector<int> &A, int sigma) : C(sigma*2), s(sigma) {
    build(A.begin(), A.end(), 0, s-1, 1);
  }

  void build(iter b, iter e, int L, int U, int u) {
    if (L == U)
      return;
    int M = (L+U)/2;

    // C[u][i] contains number of zeros until position i-1: [0,i)
    C[u].reserve(e-b+1); C[u].push_back(0);
    for (iter it = b; it != e; ++it)
      C[u].push_back(C[u].back() + (*it<=M));

    iter p = stable_partition(b, e, [=](int i){return i<=M;});

    build(b, p, L, M, u*2);
    build(p, e, M+1, U, u*2+1);
  }

  // Count number of occurrences of numbers in the range [a, b]
  // present in the sequence in positions [i, j], ie, if representing a grid it
  // counts number of points in the specified rectangle.
  mutable int L, U;
  int range(int i, int j, int a, int b) const {
    if (b < a or j < i)
      return 0;
    L = a; U = b;
    return range(i, j+1, 0, s-1, 1);
  }

  int range(int i, int j, int a, int b, int u) const {
    if (b < L or U < a)
      return 0;
    if (L <= a and b <= U)
      return j-i;
    int M = (a+b)/2, ri = C[u][i], rj = C[u][j];
    return range(ri, rj, a, M, u*2) +
      range(i-ri, j-rj, M+1, b, u*2+1);
  }
};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k, x;
    cin >> n >> k;
    vector<int> a, c;
    for(int i = 0; i < n; i++)
    {
      cin >> x;
      a.push_back(x);
    }
    vector<queue<ll> >qs(100005, queue<ll>());
    for(int i = n - 1; i >= 0; i--)
    {
      if(qs[a[i]].size() == k)
      {
        c.push_back(qs[a[i]].front());
        qs[a[i]].pop();
        qs[a[i]].push(i);
      }
      else 
      {
        c.push_back(n + 1);
        qs[a[i]].push(i);
      }
    }
    reverse(ALL(c));
    WaveTreeSucc ST(c, n + 2);
    ll last = 0, q;
    cin >> q;
    while(q--)
    {
      ll y, l, r;
      cin >> x >> y;
      l = ((x + last) % n) + 1;
      r = ((y + last) % n) + 1;
      if(l > r)swap(l, r);

      last = (r - l + 1) - ST.range(l-1, r-1, 0, r-1);
      cout << last << "\n";
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
