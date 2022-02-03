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

//https://www.spoj.com/problems/SALMAN/en/

struct SegmentTree
{
    vector<ll> ST, Lazy, STmin;
	ll N;
    ll Nul = 0;
	SegmentTree(vector<ll> &A)
	{
		N = A.size();
		ST.resize(4*N+5,0);
        STmin.resize(4*N+5, 0);
		Lazy.resize(4*N+5,Nul);

		build(1,0,N-1,A);
	}
    void up(ll n, ll l, ll r)
    {
        ST[n] += (Lazy[n] * (r - l + 1));
        STmin[n] += Lazy[n];
        if(l != r)
        {
            Lazy[n*2] += Lazy[n];
            Lazy[n*2+1] += Lazy[n];
        }
        Lazy[n] = Nul;
    }
	void build(ll n, ll l, ll r, vector<ll> &A)
	{
		if(l == r)
		{
			ST[n] = A[r];
            STmin[n] = A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);
		ST[n] = (ST[2*n] + ST[2*n+1]);
        STmin[n] = min(STmin[2*n],STmin[2*n+1]);
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

    ll query2(ll i, ll j)
	{
		return query2(1,0,N-1,i,j);
	}

	ll query2(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l ) return INF;

        up(n,l,r);


		if(i <= l && r <= j) return STmin[n];


		return min(query2(2*n,l,(l+r)/2,i,j), query2(2*n+1,(l+r)/2+1,r,i,j));
	}

	void update(ll i,ll j, ll v)
	{
		return update(1,0,N-1,i,j, v);
	}

	void update(ll n, ll l, ll r, ll i, ll j, ll v)
	{

		if(l > j || r < i)
        {
            up(n,l,r);
            return;
        }
        if(i<=l&&r<=j)
        {
            Lazy[n] += v;
            up(n,l,r);
            return;
        }
        up(n,l,r);

		update(2*n,l,(l+r)/2,i,j, v);
		update(2*n+1,(l+r)/2+1,r,i,j, v);


		ST[n] = (ST[2*n] + ST[2*n+1]);
        STmin[n] = min(STmin[2*n],STmin[2*n+1]);
	}
};
ll cont;
vl c, r, S, l;
void dfs(ll in, vector<vl>& g)
{
    c.push_back(S[in]);
    cont++;
    l[in] = cont;
    for(auto it: g[in])
    {
        dfs(it, g);
    }

    r[in] = cont;
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t, T = 0;
    cin >> t;
    while(t--)
    {
        T++;
        ll n, q;
        cin >> n >> q;
        vector<vl> g(n, vl(0));
        S.clear();
        for(int i = 0; i < n; i++)
        {
            ll s, p;
            cin >> p >> s;
            S.push_back(s);
            if(p != 0)
            {
                g[p-1].push_back(i);
            }
        }
        cont = -1;
        c.clear();
        l.assign(n, 0);
        r.assign(n, 0);
        dfs(0, g);

        SegmentTree ST(c);
        cout<<"Case "<<T<<":\n";
        while(q--)
        {
            ll C, V;
            cin >> C >> V;
            if(C == 1)
            {
                cout<<ST.query(l[V-1], r[V-1])<<"\n";
            }
            else
            {
                ll aux = ST.query2(l[V-1], r[V-1]);
                ST.update(l[V-1], r[V-1], min(1000LL, aux));
            }
            
        }
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
