#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

struct point { db x, y; 
    point() { x = y = 0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}      
    point operator + (const point& other) const
    {
        return point(this->x + other.x, this->y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }
    ll operator^(const point &p) const {return x * p.y - y * p.x; }

    // by angles but with cross
    bool half() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const point &p) const
    {
        int h1 = half(), h2 = p.half();
        return h1 != h2 ? h1 > h2 : ((*this) ^ p) > 0;
    }

    point rotate(ll mul) {

        return point( -mul * y, mul * x); }

};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, b;
    cin >> n;
    vector<pair<ll, point> >c;
    
    for(ll i = 0; i < n; i++)
    {
        point p;
        cin >> p.x >> p.y >> b;
        c.push_back({b, p});
    }
    //sort(ALL(c));

    vector<pair<point, ll> > q;
    ll cont = 0, nn = 0;
    for(ll i = 0; i < n; i++)
    {
        for(ll j = 0; j < n; j++)
        {
            
            if(c[i].first >= c[j].first)continue;
            point v = c[j].second - c[i].second;
            point aux1 = (v.rotate(1));
            point aux2 = (v.rotate(-1));
            if(aux1 < aux2) cont++;
            q.push_back({aux1, 1});
            q.push_back({aux2, 0});
            nn++;

        }
    }

    sort(ALL(q));
    bool o = 0;
    if(cont == nn) o = 1;
    for(auto it : q)
    {
        if(cont == nn) o = 1;
        if(it.second == 0)
            cont++;
        else
            cont--;
        if(cont == nn) o = 1;
    }
    if(o)cout << "Y\n";
    else cout << "N\n";
    
    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
