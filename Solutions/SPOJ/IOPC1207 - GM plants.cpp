#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://www.spoj.com/problems/IOPC1207/en/

struct SegmentTree
{
	vector<ll> ST;
    vector<bool> Lazy;
	ll N;
    ll Nul = 0;
	SegmentTree(ll n)
	{
		N = n;
		ST.resize(4*N+5,0);
		Lazy.resize(4*N+5,Nul);


	}
    void up(ll n, ll l, ll r)
    {
        if(Lazy[n]){
            ST[n] = (r - l + 1) - ST[n];
            if(l != r)
            {
                Lazy[n*2] = !Lazy[n*2];
                Lazy[n*2+1] = !Lazy[n*2+1];
            }
            Lazy[n] = Nul;
        }
    }

	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}

	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l ) return Nul;

        up(n,l,r);


		if(i <= l && r <= j) return ST[n];


		return (query(2*n,l,(l+r)/2,i,j) + query(2*n+1,(l+r)/2+1,r,i,j));
	}

	void update(ll i,ll j)
	{
		return update(1,0,N-1,i,j);
	}

	void update(ll n, ll l, ll r, ll i, ll j)
	{

		if(l > j || r < i)
        {
            up(n,l,r);
            return;
        }
        if(i<=l&&r<=j)
        {
            Lazy[n] = !Lazy[n];
            up(n,l,r);
            return;
        }
        up(n,l,r);

		update(2*n,l,(l+r)/2,i,j);
		update(2*n+1,(l+r)/2+1,r,i,j);


		ST[n] = (ST[2*n] + ST[2*n+1]);
	}
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t;
    cin >> t;
    while(t--)
    {
        ll X, Y, Z, q;
        cin >> X >> Y >> Z >> q; 
        SegmentTree STx(X), STy(Y), STz(Z);
        while(q--)
        {
            ll x, x1, x2, y1, y2, z1, z2;
            cin >> x;
            if(x == 3)
            {
                cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
                ll A = STx.query(x1, x2), B = STy.query(y1, y2), C = STz.query(z1, z2);
                ll a = x2 - x1 + 1 - A, b = y2 - y1 + 1 - B, c = z2 -z1 + 1 - C;
                cout << A*B*C + A*b*c + a*B*c + a*b*C <<"\n";
            }
            else if(x == 0)
            {
                cin >> x1 >> x2;
                STx.update(x1, x2);
            }
            else if(x == 1)
            {
                cin >> x1 >> x2;
                STy.update(x1, x2);
            }
            else if(x == 2)
            {
                cin >> x1 >> x2;
                STz.update(x1, x2);
            }
        }
    }
      

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
