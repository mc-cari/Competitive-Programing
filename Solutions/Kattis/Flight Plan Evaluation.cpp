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

//https://open.kattis.com/problems/flightplan

db DEG_to_RAD(db d) { return d*PI / 180.0; }
db R = 6370;
struct point { db x, y, z;   
    point() { x = y = z = 0.0; }                      
    //point(db r, db u, db v) : x(r*cos(u)*cos(v)), y(r*cos(u)*sin(v)), z(r*sin(u)) {}
	point(db _x, db _y, db _z) : x(_x), y(_y), z(_z) {}     
	point operator^(const point &p) const {
		return { y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y * p.x};
	}
	db dot(point& p) { return x*p.x + y*p.y + z*p.z; }
    db norm() { return sqrt(x*x + y*y + z*z); }
	
	bool operator == (const point& p) const
    {
        return abs(p.x - x) < EPS && abs(p.y - y) < EPS && abs(p.z - z) < EPS;
    }
    point operator + (const point& p) const
    {
        return point(x + p.x, y + p.y, z + p.z);
    }
    point operator - (const point& p) const
    {
        return point(x - p.x, y - p.y, z - p.z);
    }
    point operator * (db a) const
    {
        return point(x * a, y * a, z * a);
    }
    point operator / (db a) const
    {
        return point(x / a, y / a, z / a);
    }
	point unit() {
        db d = norm();
        return {x/d,y/d,z/d};
    }

};
db angle2(point& x, point& y)
{
	return acos(x.dot(y) / (R*R));
}

bool in_arc(point& p1, point& p2, point& n, point& inter)
{
	db ab = angle2(p1, p2);
	db ap = angle2(p1, inter);
	point d = (p1 * cos(ap) + (n ^ p1) * sin(ap));
	return ab > ap && inter == d;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	db c;
	cin >> c;
	vector<vector<point> > g(c, vector<point>());
	db th, lam;
	for(int i = 0; i < c; i++)
	{
		db n;
		cin >> n;
		for(int j = 0; j < n; j++)
		{
			cin >> th >> lam;
			th = DEG_to_RAD(th); lam = DEG_to_RAD(lam);
			point p(R*cos(th)*cos(lam), R*cos(th)*sin(lam), R*sin(th));
			g[i].push_back(p);
		}
	}
	db m;
	vector<point>route;
	cin >> m;
	for(int i = 0; i < m; i++)
	{
		cin >> th >> lam;
		th = DEG_to_RAD(th); lam = DEG_to_RAD(lam);
		point p(R*cos(th)*cos(lam), R*cos(th)*sin(lam), R*sin(th));
		route.push_back(p);
	}
	bool in = 1;
	db tot = 0, w = 0;
	for(int i = 0; i < m-1; i++)
	{
		vector<db> ag;
		db seg = angle2(route[i], route[i+1]);
		tot += seg;
		for(int j = 0; j < c; j++)
		{
			for(int z = 0; z < g[j].size(); z++)
			{
				point a1 = g[j][z], a2 = g[j][0];
				if(z < g[j].size() - 1)
					a2 = g[j][z+1];
				point p1 = route[i], p2 = route[i+1];
				point n1 = (p1^p2).unit(), n2 = (a1^a2).unit();
				point inter = n1^n2;
				if(inter.norm() < EPS)continue;
				inter = inter.unit() * R;
				
				if(in_arc(p1, p2, n1, inter) && in_arc(a1, a2, n2, inter))
				{	
					ag.push_back(angle2(p1, inter));
					continue;
				}
				
				inter = inter * -1.0;

				if(in_arc(p1, p2, n1, inter) && in_arc(a1, a2, n2, inter))
					ag.push_back(angle2(p1, inter));
			}
		}
		db prev = 0;
		sort(ALL(ag));
		for(auto it : ag)
		{
			if(!in)
				w += it - prev;
			prev = it;
			in = !in;
		}
		if(!in)w += seg - prev;
	}

	cout << fixed << setprecision(10) << tot * R << " " << w / tot * 100 << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
