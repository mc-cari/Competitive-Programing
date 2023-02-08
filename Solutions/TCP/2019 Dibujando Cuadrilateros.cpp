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

//https://codeforces.com/group/YjFmW2O15Q/contest/102363/attachments

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


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	ll N;
	point p;
	vector<point>Q;
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> p.x >> p.y;
		Q.push_back(p);
	}
	ll ans = 0, cuads = N * (N-1) * (N-2) * (N-3) / 24, tris = (N-1) * (N-2) * (N-3) / 6;
	for(int i = 0; i < N; i++) 
	{
		vector<point> ord;
		for(int j = 0; j < N; j++)
		{
			if(i == j)continue;
			ord.push_back((Q[j] - Q[i]));
		}
		sort(ALL(ord));
		ll n = N-1, in = 0, res = 0;
		for(int j = 0; j < n; j++)
		{
			while( in != j + n && (ord[j]^ord[(in)%n]) >= 0){
				in++;
			}
			ll cont = in - j - 1;
			res += cont * (cont-1) / 2;
		}
		ans += (tris - res);
	}
	cout << cuads - ans << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
