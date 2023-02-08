#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)



struct point { db x, y; char tipe;   
    point() { x = y = 0; }                      
    point(db _x, db _y, char _tipe) : x(_x), y(_y), tipe(_tipe){}        
    bool operator <(const point& p) const { return ( x == p.x ? y >= p.y : x <= p.x ); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y, tipe); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y, tipe); }
    point operator * (db p) const { return point(x * p, y * p, tipe); }
    point operator / (db p) const { return point(x / p, y / p, tipe); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    point rot(){ return point(-y, x, tipe); }
};


struct BIT { 
    
    vl bit;
    BIT(ll n) { bit.assign(n+1, 0); }

    ll psq(ll k) {
        ll sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
    ll rsq(ll a, ll b) {
        return psq(b) - psq(a-1);
    }
    // increment k'th value by v (and propagate)
    void add(ll k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
};

bool cmp_y(pair<point, ll> a, pair<point, ll> b) {
    if (a.first.y == b.first.y ) return a.first.x <= b.first.x;
    return a.first.y >= b.first.y;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;

    vector<pair<point, ll>> P;
    rep(i, n) {
        db x, y;
        char c;
        cin >> x >> y >> c;
        x *= 2;
        //// cout<< x << " " << y << " " << c << endl;
        point p(x + y, y - x, c);

        //// cout<< p.x << " " << p.y << " " << p.tipe << endl;
        p = p.rot();
        //// cout<< p.x << " " << p.y << " " << p.tipe << endl;
        ///// cout<< endl;
        
        P.pb({p, i});
    }
    sort(ALL(P), cmp_y);
    rep(i, n){
        P[i].second = i;
        //// cout<< P[i].first.x << " " << P[i].first.y << " " << P[i].first.tipe << " " << P[i].second << endl;
    }
    //// cout<< endl;
    sort(ALL(P));
    BIT falses(n);
    bool o = 0;
    rep(i, n) {
        
        if (P[i].first.tipe == 'P') falses.add(P[i].second+1, 1);
        if (P[i].first.tipe == 'N' && falses.psq(P[i].second+1) >= 1) o = 1;
    }
    if (o) {
        cout<< "impossible" << endl;
        return 0;
    }
    // cout<< P.size() << endl;
    vector<pair<point, ll>> Paux;
    BIT falses2(n);
    for(int i = n-1; i >= 0; i--){
        if (P[i].first.tipe == '-' && falses2.rsq(P[i].second+1, n) == 0) Paux.pb(P[i]);
        if (P[i].first.tipe == 'N') falses2.add(P[i].second+1, 1);
        else if (P[i].first.tipe == 'P') Paux.pb(P[i]);
    }
    P = Paux;
    // cout<< P.size() << endl;
    sort(ALL(P));



    vector<pair<point, ll>> P2;
    BIT useless(n);

    rep(i, P.size()) {
        // cout<< P[i].first.x << " " << P[i].first.y << " " << P[i].first.tipe << " " << P[i].second << endl;
        if (P[i].first.tipe == 'P' && useless.psq(P[i].second+1) == 0) P2.pb(P[i]);
        if (P[i].first.tipe == 'P') useless.add(P[i].second+1, 1);
        else if(P[i].first.tipe == '-') P2.pb(P[i]);
    }
    ll ans = 0;
    // cout<< P2.size() << endl;

    BIT discard1(n);
    vector<pair<point, ll>> P3;
    rep(i, P2.size()) {
        // cout<< P2[i].first.x << " " << P2[i].first.y << " " << P2[i].first.tipe << " " << P2[i].second << endl;
        if (P2[i].first.tipe == 'P' && discard1.psq(P2[i].second+1) > 0) P3.pb(P2[i]);
        if (P2[i].first.tipe == 'P' && discard1.psq(P2[i].second+1) == 0) ans++;
        if (P2[i].first.tipe == '-') {
            discard1.add(P2[i].second+1, 1);
            P3.pb(P2[i]);
        }
    }

    // cout<< P3.size() << "*" << ans << endl;

    sort(ALL(P3), cmp_y);

    db possible_left = INF, true_left = INF;

    for(auto it : P3) {
        // cout<< it.first.x << " " << it.first.y << " " << it.first.tipe << " " << it.second << endl;
        if (it.first.tipe == '-') {
            possible_left = min(possible_left, it.first.x);
        }
        if (it.first.tipe == 'P') {
            if (it.first.x < true_left - EPS) {
                ans++;
                true_left = min(possible_left, it.first.x);
            }
        }
    }
    cout<< ans << endl;

}