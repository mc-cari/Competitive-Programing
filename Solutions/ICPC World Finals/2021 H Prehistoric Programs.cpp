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


struct SegmentTree
{
	vl ST; ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, 0);
		bd(1,0,N-1,A);
	}
	ll op(ll x, ll y) { return max(x,y); }
	void bd(ll n, ll l, ll r, vl &A)
	{
		if(l == r)
		{
			ST[n] = A[r];
			return;
		}
		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);
		ST[n] = op(ST[2*n], ST[2*n+1]);
	}
	ll qry(ll i, ll j)
	{
		return qry(1,0,N-1,i,j);
	}
	ll qry(ll n, ll l, ll r, ll i, ll j)
	{
		if(r < i || j < l) return -INF;
		if(i <= l && r <= j) return ST[n];

		return op(qry(2*n,l,(l+r)/2,i,j), qry(2*n+1,(l+r)/2+1,r,i,j));
	}
	void upd(ll i, ll v)
	{
		return upd(1,0,N-1,i,v);
	}
	void upd(ll n, ll l, ll r, ll i, ll v)
	{
		if(i < l || r < i) return;
		if(l == r)
		{
			ST[n] = v;
			return;
		}

		upd(2*n,l,(l+r)/2,i,v);
		upd(2*n+1,(l+r)/2+1,r,i,v);
		ST[n] = op(ST[2*n], ST[2*n+1]);
	}
};


int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll n;
	cin >> n;
	vl ans;
	ll ac = 0;

	vector<tuple<ll, ll, ll>> pend;
	rep(i, n){
		
		string s;
		cin >> s;
		ll mini = 0, sum = 0;
		for(auto it : s){
			if(it == '(')sum++;
			else sum--;
			mini = min(mini, sum);
			
		}
		pend.pb({mini, sum, i+1});

	}
	sort(ALLR(pend));
	vl vis(n, 0);
	rep(i, n){
		if(ac + get<0>(pend[i]) >= 0 && get<1>(pend[i]) >= 0){
			ac += get<1>(pend[i]);
			ans.pb(get<2>(pend[i]));
			vis[i] = 1;
		}
	}
	bool o = 1;


	vl c;
	rep(i, n){
		if(vis[i] == 0){
			c.pb(get<1>(pend[i]));
		}
		else c.pb(-INF);
		
	} 



	SegmentTree st(c);
	for(int i = n-1; i >= 0; i--){
		if(vis[i])continue;
		ll rest = ac + get<0>(pend[i]);
		if(rest < 0){
			o = 0;
			break;
		}
		ll res = 1;
		while(res != -1){
			ll l = 0, r = i-1, res = -1;
			while(l <= r)
			{
				ll p = (l + r) / 2;
				if(st.qry(p, i-1) + rest >= 0){
					l = p+1;
					res = p;
				}
				else r = p-1;
			}
			if(res == -1)break;
			
			st.upd(res, -INF);
			rest += get<1>(pend[res]);
			ans.pb(get<2>(pend[res]));
			vis[res] = 1;
			ac += get<1>(pend[res]);
		}

		if(ac + get<0>(pend[i]) >= 0){
			ac += get<1>(pend[i]);
			ans.pb(get<2>(pend[i]));
			vis[i] = 1;
		}
		else o = 0;
	}
	
	if(!o || ac != 0){
		cout << "impossible\n";
	}
	else{
		for(auto it : ans ) cout << it << "\n";
	}


	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}