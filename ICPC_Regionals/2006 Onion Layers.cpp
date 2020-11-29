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

//https://www.urionlinejudge.com.br/judge/es/problems/view/1464

struct point { db x, y; 
    point() { x = y = 0; }                      
    point(db _x, db _y) : x(_x), y(_y) {} 
    bool operator == (const point& other) const
    {
        return abs(other.x - x) < EPS && abs(other.y - y) < EPS;
    }  
    bool operator <(const point& other) const
    {
        return (x < other.x ? true : (x == other.x && y < other.y));
    }   
    point operator + (const point& other) const
    {
        return point(this->x + other.x, this->y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }
    ll operator^(const point &p) const {return x * p.y - y * p.x; }

    db ang()
    {
        db a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }
    
};

struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }



db cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) >= 0; }
vector<point> CH_Andrew(vector<point> &Pts) {
  ll n = Pts.size(), k = 0;
  vector<point> H(2*n);
  sort(Pts.begin(), Pts.end());        // sort the points lexicographically
  for (ll i = 0; i < n; i++) {                         // build lower hull
    while (k >= 2 && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  for (ll i = n-2, t = k+1; i >= 0; i--) {             // build upper hull
    while (k >= t && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    while(cin >> n && n){
        point p;
        vector<point> Q;
        for(int i = 0; i < n; i++)
        {
            cin >> p.x >> p.y;
            Q.push_back(p);
        }
        sort(ALL(Q));
        UNIQUE(Q);
        ll ans = 0;
        while(Q.size() > 2)
        {
            vector<point> H = CH_Andrew(Q);
            set<point> L;
            for(auto it : H)L.insert(it);
            vector<point> aux;

            for(auto it : Q)
                if(!L.count(it))
                {
                    aux.push_back(it);
                }
            swap(aux, Q);
            ans++;
        }
        if(ans % 2 == 1)cout << "Take this onion to the lab!\n";
        else cout << "Do not take this onion to the lab!\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
