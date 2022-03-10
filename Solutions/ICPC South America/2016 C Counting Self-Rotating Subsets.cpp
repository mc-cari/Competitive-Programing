#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e9
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://www.beecrowd.com.br/judge/es/problems/view/2347

ll M = 1e9 + 7;

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }


};

const ll MAXN = 1e4 + 1;
ll F[MAXN], INV[MAXN], FI[MAXN];
// ...
ll Comb(ll n, ll k){
    return F[n]*FI[k] %M *FI[n-k] %M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    F[0] = 1; for(ll i = 1; i < MAXN; i++) F[i] = F[i-1]*i %M;
    INV[1] = 1; for(ll i = 2; i < MAXN; i++) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
    FI[0] = 1; for(ll i = 1; i < MAXN; i++) FI[i] = FI[i-1]*INV[i] %M;
    
    ll n;
    cin >> n;
    point p;
    vector<point> Q;
    map<pll, ll> m, cont;
    for(int i = 0; i < n; i++)
    {
        cin >> p.x >> p.y;
        p = p*2;
        Q.push_back(p);
        m[{p.x, p.y}]++;

    }
    vl ans(n, 0);
    ans[0] = n;
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            point aux = (Q[i] + Q[j])/2;
            cont[{aux.x, aux.y}]++;
        }
    }

    for(auto it : cont)
    {
 
        for(int i = 1; i <= it.second; i++)
        {
            ll aux = Comb(it.second, i);
            if(m[it.first]){
                ans[2*i] += aux;
                ans[2*i] %= M;
            }
            ans[2*i-1] += Comb(it.second, i);
            ans[2*i-1] %= M;
        }
      
    }
    for(int i = 0; i < n; i++)
    {
        cout << ans[i];
        if(i < n-1) cout << " ";
        else cout << "\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
