#include<bits/stdc++.h>
 
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
 
// https://codeforces.com/gym/103185/problem/I
 
struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }

    // by angles but with cross
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

ll M = 1e9+7;
ll memo[302][302];

bool ccw(point p, point q, point r) {
  return ((q - p)^(r - p)) > 0; }


point ph, pg, p;
deque<point> Q;

ll dp(ll i, ll j)
{
   
    if(!ccw(Q[i], Q[j], {0,0}))return 0;

    if(i == 0) return 1;
    if(memo[i][j] != -1)return memo[i][j];
    ll ans = 0;
    
    for(int k = 0; k < j; k++) {
        if(ccw(Q[k], Q[i], Q[j]))
        {
            ans += dp(k, i);
            ans %= M;
        }
    }
    return memo[i][j] = ans;
}

 
int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    memset(memo, -1, sizeof(memo));
    
    
    cin >> ph.x >> ph.y;

    cin >> pg.x >> pg.y;
    pg = (pg - ph);
    Q.push_back(pg);
    ll n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> p.x >> p.y;
        Q.push_back(p - ph);

    }
    sort(ALL(Q));

    while(!(Q.back() == pg)){
        Q.push_front(Q.back());
        Q.pop_back();
    }
    Q.push_front(pg);

    ll ans = 0;
    for(int j = 1; j < Q.size()-1; j++)
    {
        ans += dp(j, Q.size()-1);
        ans %= M;
    }
    cout << ans << "\n";
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
