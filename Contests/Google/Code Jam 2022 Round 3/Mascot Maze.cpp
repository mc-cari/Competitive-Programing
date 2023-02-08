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

  // Count occurrences of number c until position i.
  // ie, occurrences of c in positions [i,j]
  int rank(int c, int i) const {
    // Internally we consider an interval open on the left: [0, i)
    i++;
    int L = 0, U = s-1, u = 1, M, r;
    while (L != U) {
      M = (L+U)/2;
      r = C[u][i]; u*=2;
      if (c <= M)
        i = r, U = M;
      else
        i -= r, L = M+1, ++u;
    }
    return i;
  }

  // Find the k-th smallest element in positions [i,j].
  // The smallest element is k=1
  int quantile(int k, int i, int j) const {
    // internally we we consider an interval open on the left:  [i, j)
    j++;
    int L = 0, U = s-1, u = 1, M, ri, rj;
    while (L != U) {
      M = (L+U)/2;
      ri = C[u][i]; rj = C[u][j]; u*=2;
      if (k <= rj-ri)
        i = ri, j = rj, U = M;
      else
        k -= rj-ri, i -= ri, j -= rj,
          L = M+1, ++u;
    }
    return U;
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



struct BIT { // BIT = binary indexed tree (a.k.a. Fenwick Tree)
    /*

       ********All Index starts at 1**********

    */
    vl bit;
    BIT(ll n) { bit.assign(n+1, 0); }
    // prefix sum query (sum in range 1 .. k)
    ll psq(ll k) {
        ll sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
    // range sum query (sum in range a .. b)
    ll rsq(ll a, ll b) {
        return psq(b) - psq(a-1);
    }
    // (1, r)
    ll getmin(ll r) {
        ll ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    // increment k'th value by v (and propagate)
    void add(ll k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
    void set(ll k, ll v)
    {
        ll aux=rsq(k,k);
        for (; k < bit.size(); k += (k & -k)) bit[k] += v-aux;
        //bit[idx] = min(bit[idx], val);
    }
};

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

    
    ll T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
        ll N, C;
        cin >> N >> C;
        vp info;
        vl c;
        ll x, y;
        for(int i = 0; i < C; i++)
        {
            cin >> x >> y;
            info.push_back({x, y});
        }
        for(int i = 0; i < N; i++)
        {
            cin >> x;
            c.push_back(x-1);
        }
        for(int i = 0; i < N; i++) c.push_back(c[i]);

        //WaveTreeSucc wt(c, C+1);

        ll ans = 0;
        for(int i = 0; i < N; i++)
        {
            vl cl(C, 0);
            BIT bit(C);

            for(int j = 0; j < C; j++)
            {
                bit.add(j+1, 1);
            }
 
            for(int j = 0; j < N-1; j++)
            {

                cl[c[i+j]]++;
                if(info[c[i+j]].first > cl[c[i+j]]) bit.set(c[i+j] + 1, 0);
                else if(info[c[i+j]].second < cl[c[i+j]]) bit.set(c[i+j] + 1, 0);
                else bit.set(c[i+j] + 1, 1);
                ll o = bit.psq(C);

                if(o == C && j != 0) ans++;
            }
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }



    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}