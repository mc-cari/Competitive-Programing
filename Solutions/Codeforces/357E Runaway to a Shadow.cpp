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

//https://codeforces.com/contest/681/problem/E

struct point { db x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(db _x, db _y) : x(_x), y(_y) {}        // user-defined
    bool operator <(const point& other) const
    {
        return (x < other.x ? true : (x == other.x && y < other.y));
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

    db x, y, v, t, n, r;
    point p, e;
    cin >> p.x >> p.y >> v >> t;
    cin >> n;
    db T = t * v  * 1.0;

    vector<pair<db, db> > q;
    bool o = 0;
    db acum = 0, sum = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> x >> y >> r;
        x -= p.x;
        y -= p.y;
        point center(x, y);
        db l1, l2;
        if(ll(x * x + y * y) - ll(r*r) < EPS) o = 1;
        if(x * x + y * y >= (r + T) * (r + T) || r == 0)continue;
        
        

        if (T * T >=  x * x + y * y - r * r)
        {
            db aux = - r * r + x * x + y * y;

            l1 = center.ang() - acos((r * r - aux - (x * x + y * y)) / (-2*sqrt(aux)*sqrt(x * x + y * y)));
            l2 = center.ang() + acos((r * r - aux - (x * x + y * y)) / (-2*sqrt(aux)*sqrt(x * x + y * y)));
            
        }
        else
        {
            l1 = center.ang() - acos((r * r - T * T - (x * x + y * y)) / (-2*T*sqrt(x * x + y * y)));
            l2 = center.ang() + acos((r * r - T * T - (x * x + y * y)) / (-2*T*sqrt(x * x + y * y)));
        }
        if (l1 < 0)l1 += 2 * PI;
        if (l2 > 2*PI)l2 -= 2 * PI;
        if(l1 > l2) acum ++;
        q.push_back({l1, 1});
        q.push_back({l2, -1});
        
    }
    if(o)
    {
        cout << "1.00\n";
        return 0;
    }
    sort(ALL(q));
    db prev = 0;
    for(auto it : q)
    {
        if(it.second == -1)
        {
            if(acum == 1)
            {
                sum += it.first - prev;
            }
            acum--;
        }
        else
        {
            if(acum == 0){
                prev = it.first;
            }
            acum ++;
        }
        
    }
    if (acum != 0) sum += 2*PI - prev;
    cout << fixed << setprecision(6) << sum / (2.0*PI) << "\n";
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
