  #include<bits/stdc++.h>
  #pragma GCC optimize("Ofast")
  using namespace std;
  typedef long long ll;
  typedef vector<ll> vl;
  typedef pair<ll, ll> pll;
  #define ff first
  #define ss second
  #define pb push_back
  #define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

  #define rep(i, n) for(int i = 0; i < (int)n; i++)

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
      vector<int> rev(n);
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


  vd conv(const vl &a, const vl &b)
  {
      if (a.empty() || b.empty()) return {};
      vd res(a.size() + b.size() - 1);
      int L = 32 - __builtin_clz(res.size()), n = 1 << L;
      vector<C> in(n), out(n);
      copy(a.begin(), a.end(), in.begin());
      rep(i, b.size()) in[i].imag(b[i]);
      fft(in);
      for (auto &x : in) x *= x;
      rep(i, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
      fft(out);
      rep(i, res.size()) res[i] = imag(out[i]) / (4 * n);
      return res;
  }

  int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, p;
    cin >> n >> p;
    string s;
    cin >> s;


    string s2 = s + s.substr(0, n-1);
    vl an(2*n-1, 0), am(n, 0), bn(2*n-1, 0), bm(n, 0), cn(2*n-1, 0), cm(n, 0);

    rep(i, 2*n-1)
    {
      if(s2[i] == 'B')
        an[i] = 1;
      else if(s2[i] == 'R')
        bn[i] = 1;
      else
        cn[i] = 1;
    }

    rep(i, n)
    {
      if(s[i] == 'B')
        am[i] = 1;
      else if(s[i] == 'R')
        bm[i] = 1;
      else
        cm[i] = 1;
    }

    reverse(am.begin(), am.end());
    reverse(bm.begin(), bm.end());
    reverse(cm.begin(), cm.end());

    vd resA= conv(an,am);
    vd resB = conv(bn,bm);
    vd resC= conv(cn,cm);


    vl A, F(500001, 0), Pre, Suf(500001, 0);
    for (int i = n; i < n-1+n; ++i) {
      A.push_back(n - round(resA[i]) - round(resB[i]) - round(resC[i]));
      
    }

    rep(i, n-1)
    {
      F[A[i]]++;
    
    }

    rep(i, 500001)
    {
      Pre.push_back(F[i]);
      Suf[500001-i-1]=(F[500001-i-1]);
      if(i != 0)
      {
        Pre[i] += Pre[i-1];
        Suf[500001-i-1] += Suf[500001-i];
      }
    }
    p--;
    int ans=-1;
    rep(i, n)
    {
      //cout << Pre[A[i]] - (F[A[i]] >= 1) << " "<<Suf[A[i]] - (F[A[i]] >=1)<<" "<<(F[A[i]] >= 1)<<" "<<Pre[A[i]]<<" "<<F[A[i]]<<" "<<A[i]<<endl;
      if(Pre[A[i]] - (F[A[i]] >= 1) >= p && Suf[A[i]] - (F[A[i]] >=1) >= n-p-2)
      {
        
        ans = i;
        break;
      }
    }

    cout << ans+1 << "\n";

    return 0;
  }