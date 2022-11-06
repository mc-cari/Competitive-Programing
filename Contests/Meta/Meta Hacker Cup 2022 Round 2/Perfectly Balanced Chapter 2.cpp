#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF LLONG_MAX
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

ll M = 1e9 + 9;

vector <bool> crib;
void criba(ll b)
{
    crib.assign(b, 1);
    crib[0] = 0;
    crib[1] = 0;
    repx(k, 2, sqrt(b+1) + 1)
        if(crib[k])
            for(int j=2; (j * k) < b + 1; j++)//optimization j=k
                crib[k*j] = 0;
}

struct SegmentTree
{
	vl ST; ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, 0);
		bd(1,0,N-1,A);
	}
	ll op(ll x, ll y) { return (x * y) % M; }
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
		if(r < i || j < l) return 1;
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

struct SegmentTreeSum
{
	vl ST; ll N;
	SegmentTreeSum(vl &A)
	{
		N = A.size();
		ST.assign(4*N, 0);
		bd(1,0,N-1,A);
	}
	ll op(ll x, ll y) { return (x + y) % M; }
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
		if(r < i || j < l) return 0;
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

ll expmod(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b %M;
        b = b*b %M; e >>= 1;
    }
    return ans;
}

ll invmod(ll a){ return expmod(a, M-2); }

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	criba(20000000);
	vl primes;
	unordered_map<ll,ll> mp;
	repx(i, 2, 20000000) {
		if(crib[i]) {
			mp[i] = primes.size();
			primes.pb(i);
		}
		if(primes.size() == 1000000) break;
	}

	ll t;
	cin >> t;
	repx(T, 1, t+1){
		ll n, x, ans = 0;
		cin >> n;
		vl a(n), b;
		rep(i, n) {
			cin >> a[i];
			b.pb(primes[a[i]-1]);
		}
		SegmentTree ST(b);
		SegmentTreeSum STS(b);
		ll q;
		cin >> q;
		while(q--){
			ll ty;
			cin >> ty;
			if(ty == 1){
				ll x, y;
				cin >> x >> y;
				x--; y--;
				ST.upd(x, primes[y]);
				STS.upd(x, primes[y]);
			}
			else{
				ll l, r;
				cin >> l >> r;
				if((r - l) % 2 == 1)continue;
				r--; l--;
				ll val1 = ST.qry(l, (l+r)/2), val2 = ST.qry((l+r)/2+1, r);
				ll aux = val1 * invmod(val2) % M;

				ll val3 = STS.qry(l, (l+r)/2), val4 = STS.qry((l+r)/2+1, r);
				ll aux2 = (val3 - val4 + M) % M;
				if(mp.count(aux) && aux == aux2) ans++;
				else{
					  val1 = ST.qry(l, (l+r)/2-1); val2 = ST.qry((l+r)/2, r);
				    aux = val2 * invmod(val1) % M;
						val3 = STS.qry(l, (l+r)/2-1); val4 = STS.qry((l+r)/2, r);
						aux2 = (val4 - val3 + M) % M;
						if(mp.count(aux) && aux == aux2) ans++;
				}
			}
		}
		cout << "Case #" << T << ": " << ans << "\n";
	}

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}