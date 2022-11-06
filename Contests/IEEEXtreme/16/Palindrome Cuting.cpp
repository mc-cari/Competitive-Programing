#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF LLONG_MAX
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (ll i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

//https://csacademy.com/contest/ieeextreme-practice/task/palindrome-cutting

ll MOD  = 998244353;

#define M_PIl 3.141592653589793238462643383279502884L

typedef complex<double> C;
typedef vector<double> vd;

void fft(vector<C> &a)
{
    int n = a.size(), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    for (static int k = 2; k < n; k *= 2)
    {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, M_PIl / k);
        repx(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vector<ll> rev(n);
    rep(i, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) for (int i = 0; i < n; i += 2 * k) rep(j, k)
    {
        auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k];
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
    }
}

vector<int> convMod(const vl &a, const vl &b, ll M)
{
    if (a.empty() || b.empty()) return {};
    vector<int> res(a.size() + b.size() - 1);
    ll B = 32 - __builtin_clz(res.size()), n = 1LL << B, cut = ll(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i, a.size()) L[i] = C((ll)a[i] / cut, (ll)a[i] % cut);
    rep(i, b.size()) R[i] = C((ll)b[i] / cut, (ll)b[i] % cut);
    fft(L), fft(R);
    rep(i, n)
    {
        ll j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i, res.size())
    {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}
vl F, R;

void solve(ll l, ll r){

  if(r - l <= 1) return;

  ll m = (l + r) / 2;
  solve(l, m);

  vl Rs(R.begin() + l, R.begin() + m);
  vl Fs(F.begin() + 1, F.begin() + r - l);

  vector<int> ans = convMod(Rs, Fs, MOD);

  repx(i, m-1, r-1){

    R[i+1] += ans[i-l];
    R[i+1] %= MOD;
  }

  solve(m, r);
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

  vector<int> b(1000, 0);
  ll N, M;
  cin >> N >> M;
  N /= 2;
  

  F.assign(N + 2, 0);
  R.assign(N + 2, 0);
  F[0] = 0;
  F[1] = M;
  F[2] = M * (M - 1) % MOD; 
  repx(i, 3, N + 1){
    if(i % 2)F[i] = F[i - 1] * M % MOD;
    else F[i] = (((M*M)%MOD) * F[i-2] % MOD - F[i/2] + MOD) % MOD;
  }

  cerr << "b:";
    for (ll x : F) cerr << " " << x;
  cerr << endl;
  R[0] = 1;
  solve(0, N+1);

  cout << R[N] << endl;

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}