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


#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

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
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, x;
    cin >> n;  
    vl c, d, posc, posd, aux, aux2;

    for(int i = 0; i < n; i++)
    {
        cin >> x;
        aux.push_back(x);
        if(x < 0)
            c.push_back(x);
        else
            posc.push_back(x);
    }
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        aux2.push_back(x);
        if(x < 0)
            d.push_back(x);
        else
            posd.push_back(x);
    }
    sort(ALL(posc));
    sort(ALL(posd));
    sort(ALLR(c));
    sort(ALLR(d));

    vl mul1, ans1;
    while(!posc.empty() && !posd.empty()){
        mul1.push_back(posc.back() * posd.back());
        posc.pop_back();
        posd.pop_back();
    }
    while(!c.empty() && !d.empty()){
        mul1.push_back(c.back() * d.back());
        c.pop_back();
        d.pop_back();
    }

    ll ans = 0;
    sort(ALLR(mul1));
    for(auto it : mul1)
    {
        ans += it;
        ans1.push_back(ans);
    }

    if(posc.empty())swap(posc, posd);
    if(c.empty()) swap(c, d);

    //reverse(ALL(posc));

    vd res1 = conv(c, posc);

    for(int i = 0; i < c.size(); i++)
    {
        ans1.push_back(ans + round(res1[i]));
    }

    c.clear();
    d.clear();
    posc.clear();
    posd.clear();
    for(auto it : aux)
    {

        if(it < 0)
            c.push_back(it);
        else
            posc.push_back(it);
    }
    for(auto it : aux2)
    {

        if(it < 0)
            d.push_back(it);
        else
            posd.push_back(it);
    }
    sort(ALL(posc));
    sort(ALL(posd));
    sort(ALLR(c));
    sort(ALLR(d));

    vl mul2, ans2;
    while(!posc.empty() && !d.empty()){
        mul2.push_back(posc.back() * d.back());
        posc.pop_back();
        d.pop_back();
    }
    while(!c.empty() && !posd.empty()){
        mul2.push_back(c.back() * posd.back());
        c.pop_back();
        posd.pop_back();
    }

    ans = 0;
    sort(ALL(mul2));
    for(auto it : mul2)
    {
        ans += it;
        ans2.push_back(ans);
    }

    if(posc.empty())swap(posc, d);
    if(c.empty()) swap(c, posd);

    
    vd res2 = conv(c, posc);

    for(int i = 0; i < c.size(); i++)
    {
        ans2.push_back(ans + round(res2[i]));
    }


    for(int i = 0; i < n; i++)
    {
        cout << ans2[i] << " " << ans1[i] << "\n";
    }
    

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}