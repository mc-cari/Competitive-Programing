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

//https://codeforces.com/contest/1284/problem/E

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        

    bool operator == (const point& other) const
    {
        return abs(other.x - x) < EPS && abs(other.y - y) < EPS;
    }

    point operator + (const point& other) const
    {
        return point(this->x + other.x, this->y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }
    point operator * (long double other) const
    {
        return point(this->x * other, this->y * other);
    }
    ll operator^(const point &p) const {return x * p.y - y * p.x; }
    point operator / (long double other) const
    {
        return point(this->x / other, this->y / other);
    }
    bool half() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const point &p) const
    {
        int h1 = half(), h2 = p.half();
        return h1 != h2 ? h1 > h2 : ((*this) ^ p) > 0;
    }

    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	ll n;
    point p;
    cin >> n;
    vector<point>Q;
    for(int i = 0; i < n; i++)
    {
        cin >> p.x >> p.y;
        Q.push_back(p);
    }
    ll ans = (n-1)*(n-2)*(n-3)*(n-4)/24 * n;
    for(int i = 0; i < n; i++)
    {
        vector<point>c;
        for(int j = 0; j < n; j++)
        {
            if(j == i)continue;
            c.push_back(Q[j] - Q[i]);
        }
        sort(ALL(c));
        ll in = 0;
        for(int j = 0; j < n - 1; j++)
        {
            while(j + n - 1 > in && (c[j]^c[in%(n-1)]) >= 0)in++;
            ll res = in - 1 - j;
            if(res > 0)
                ans -= res*(res-1)*(res-2)/6;
        }
    }
    cout << ans << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
