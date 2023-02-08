#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/CERC07C/

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
db dist(point& p1, point& p2) {            
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); }
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); } 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	db n, r;
    while(cin >> n >> r && (n + r)){
        point p;
        vector<point>Q;
        ll ans = 0;
        for(int i = 0; i < n; i++)
        {
            cin >> p.x >> p.y;
            Q.push_back(p);
        }
        for(int i = 0; i < n; i++)
        {
            vector<pair<db, db> >sweep;
            ll cont = 0;
            for(int j = 0; j < n; j++)
            {
                if(i == j)continue;
                db d = dist(Q[i], Q[j]);
                if(d > 2*r)continue;
                db th = acos(d/(2*r));
                db aux = th + (Q[j] - Q[i]).ang();
                if(aux > 2*PI)aux -= 2*PI;
                if(aux < 0)aux += 2*PI;
                sweep.push_back({aux, 1});
                db aux2 = -th + (Q[j] - Q[i]).ang();
                if(aux2 < 0)aux2 += 2*PI;
                if(aux2 > 2*PI)aux2 -= 2*PI;
                sweep.push_back({aux2, 0});

                if(aux2 > aux)cont++;
            }
            sort(ALL(sweep));
            ll maxi = 0;
            maxi = max(maxi, cont);
            for(auto it : sweep)
            {
                if(it.second == 0)cont++;
                else cont--;
                maxi = max(maxi, cont);
            }
            ans = max(ans, 1 + maxi);
        }
        cout << "It is possible to cover " << ans << " points.\n";
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
