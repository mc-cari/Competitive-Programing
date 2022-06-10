#include "../Header.cpp"
/*
beats
node(suma, max, max2, cant_max)

*/

struct SegmentTree
{
	vl ST;
	ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, 0);
		build(1,0,N-1,A);
	}
	void bd(ll n, ll l, ll r, vl &A)
	{
		if(l == r)
		{
			ST[n] = A[r];
			return;
		}

		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);

		ST[n] = ST[2*n]+ST[2*n+1];
	}
	ll qry(ll i, ll j)
	{
		return qry(1,0,N-1,i,j);
	}
	ll qry(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return 0;

		if(i <= l && r <= j) return ST[n];

		return (qry(2*n,l,(l+r)/2,i,j)+qry(2*n+1,(l+r)/2+1,r,i,j));
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

		ST[n] = ST[2*n] + ST[2*n+1];
	}
};

