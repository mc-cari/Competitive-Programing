#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

//https://codeforces.com/group/4zVk9dZl6Q/contest/390678/problem/A
struct SegmentTree
{
	vector<ll> ST,Lazy;
	ll N, Nul = 0;
	SegmentTree(ll n)
	{
		N = n;
		ST.resize(4*N+5,0);
		Lazy.resize(4*N+5,Nul);

	}
    void up(ll n, ll l, ll r)
    {
        ST[n] += Lazy[n];
        if(l != r)
        {
            Lazy[n*2] += Lazy[n];
            Lazy[n*2+1] += Lazy[n];
        }
        Lazy[n] = Nul;
    }
	ll op(ll x, ll y) { return max(x,y); }


	ll qry(ll i, ll j)
	{
		return qry(1,0,N-1,i,j);
	}
	ll qry(ll n, ll l, ll r, ll i, ll j)
	{
		if(r < i || j < l ) return Nul;
        if(Lazy[n]) up(n,l,r);
		if(i <= l && r <= j) return ST[n];
		return op(qry(2*n,l,(l+r)/2,i,j), qry(2*n+1,(l+r)/2+1,r,i,j));
	}
	void upd(ll i,ll j, ll v)
	{
		return upd(1,0,N-1,i,j,v);
	}
	void upd(ll n, ll l, ll r, ll i, ll j, ll v)
	{
		if(Lazy[n]) up(n,l,r);
		if(l > j || r < i)
        {
            return;
        }
        if(i <= l && r <= j)
        {
            Lazy[n] += v;
            if(Lazy[n]) up(n, l, r);
            return;
        }

		upd(2*n,l,(l+r)/2,i,j,v);
		upd(2*n+1,(l+r)/2+1,r,i,j,v);
		ST[n] = op(ST[2*n], ST[2*n+1]);
	}
};




int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);


	ll n, k, maxi = 2.5e5 + 200;
	cin >> n >> k;
	vector<tuple<ll, ll, ll>>P;
	rep(i, n)
	{
		ll x, y, c;
		cin >> x >> y >> c;
		c--;
		x--;
		y--;
		maxi = max({maxi, x, y});
		P.pb({x, y, c});
	}

	ll l = 0, r = maxi, p, res = -1;
	while(l <= r)
	{
		p = (l + r) / 2;
		bool o = 0;
		vector<tuple<ll, ll, ll>> sweep;
		SegmentTree ST(maxi + 1 + p);
		rep(i, n)
		{
			ll x, y, c;
			tie(x, y, c) = P[i];
			sweep.pb({x, 0, i}); // enter
			sweep.pb({x + p, 1, i}); // exit
		}
		sort(ALL(sweep));
		vector<multiset<ll>> color(k, multiset<ll>());
		rep(i, k)
		{
			color[i].insert(-1);
			color[i].insert(maxi+p+1);
		}
		for(auto it : sweep)
		{
			ll x, type, in, y, c;
			tie(x, type, in) = it;
			tie(x, y, c) = P[in];

			if(type == 1)
			{
				color[c].erase(color[c].find(y));
			}

			auto itr = color[c].lower_bound(y);
			auto itl = prev(itr);
			ll L = max(*itl+1, y- p);
			ll R = min(*itr-p-1, y);

			if(R >= L) type == 0 ? ST.upd(L, R, 1) : ST.upd(L, R, -1);
			if(ST.qry(0, maxi+p) == k)
			{
				o = 1;
				break;
			}
			if(type == 0)
			{
				color[c].insert(y);
			}
		}

		if(!o)l = p+1;
		else 
		{
			r = p-1;
			res = p;
		}
	}
	cout << res << "\n";

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
