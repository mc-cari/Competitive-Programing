#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
using ll = long long;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)


struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }
};
db dist(const point& p1,const point& p2) {             
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }

//Scalar projection of vector a onto vector b
db sproject(point a, point b)
{
  return a*b/sqrt(b.norm_sq());
}
db RAD_to_DEG(db r) { return r*180.0 / PI; }

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll n, m;
	cin >> n >> m;
	vector<vector<point>> polygons(n, vector<point>());
	rep(i, n){
		ll k;
		cin >> k;
		polygons[i].resize(k);
		rep(j, k){
			point p;
			cin >> p.x >> p.y;
			polygons[i][j] = p;
		}
	}	
	vector<db> min_angle(n, INF);

	rep(i, m){
		point p1, p2;
		db z1, z2;
		cin >> p1.x >> p1.y >> z1 >> p2.x >> p2.y >> z2;

		db eq1 = (z2 - z1) / dist(p1, p2), eq2 = z1;
		rep(j, n){
			db max_angle = 0;
			bool o = 1;
			for(auto it : polygons[j]){
				db s = sproject(it - p1, p2 - p1);
				if(s < -EPS || s > dist(p1, p2) + EPS){
					o = 0;
					break;
				}
				db h = sqrt(dist_sq(it, p1) - s*s);
				db z = eq1 * s + eq2;
				db angle = atan2(h, z);
				max_angle = max(max_angle, angle);
			}
			if(!o)continue;
			min_angle[j] = min(min_angle[j], max_angle);
		}
	}

	db ans = 0;
	rep(i, n){
		ans = max(min_angle[i], ans);
	}
	if(ans == INF)cout << "impossible\n";
	else cout << fixed << setprecision(10) << RAD_to_DEG(ans) << "\n";

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}