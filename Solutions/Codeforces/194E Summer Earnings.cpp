#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef int db;
#define INF 1e12
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/contest/333/problem/E

struct SegmentTree
{
	vector<double> ST;
	ll N;
	SegmentTree(vector<double> &A)
	{
		N = A.size();
		ST.resize(4*N);
		build(1,0,N-1,A);
	}
	void build(ll n, ll l, ll r, vector<double> &A)
	{
		if(l==r)
		{
			ST[n]=A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		ST[n] = max(ST[2*n],ST[2*n+1]);
	}
	double query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}
	double query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return 0;

		if(i <= l && r <= j) return ST[n];

		return max(query(2*n,l,(l+r)/2,i,j),query(2*n+1,(l+r)/2+1,r,i,j));
	}

};


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
    double norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }
    
    // by angles but with cross
    bool half() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const point &p) const
    {
        int h1 = half(), h2 = p.half();
        return h1 != h2 ? h1 > h2 : ((*this) ^ p) > 0;
    }

    double ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    ll n;
    cin >> n;
    vector<point>Q;
    point p;
    for(int i = 0; i < n; i++)
    {
        cin >> p.x >> p.y;
        Q.push_back(p);
    }
    double maxi = 0.0;
    for(int i = 0; i < n; i++)
    {
        vector<point> D;
        for(int j = 0; j < n; j++)
        {
            if(i != j)D.push_back(Q[j] - Q[i]);
        }
        sort(ALL(D));
        vector<double> an, A;
        for(int j = 0; j < n-1; j++)D.push_back(D[j]);
        for(int j = 0; j < 2*(n-1); j++)
        {
            an.push_back(D[j].ang());
            if(j >= n-1)an.back() += 2*PI;
            A.push_back(sqrt(D[j].norm_sq()));
        }
        SegmentTree ST(A);
        ll p1 = 0, p2 = 0;
        
        

        for(int j = 0; j < n-1; j++)
        {
            while(an[j + n-1] - an[p2] >= PI/3)
            {
                
                p2++;
            }
            while(an[p1] - an[j] < PI/3)
            {
                
                p1++;
            }
            //cout<<p1<<" "<<p2<<"\n";
            if(p1 < p2 && p2 != 0 && ST.query(p1, p2-1) >= sqrt(D[j].norm_sq())) maxi = max(maxi, sqrt(D[j].norm_sq()));
        }
    }
    cout << fixed << setprecision(10) << maxi/2.0 << "\n";
   
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
