#include "../Header.cpp"

struct SegmentTree
{
	vl ST; int N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, 0);
		bd(1,0,N-1,A);
	}
	ll op(ll x, ll y) { return min(x,y); }
	void bd(int n, int l, int r, vl &A)
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
	ll qry(int i, int j)
	{
		return qry(1,0,N-1,i,j);
	}
	ll qry(int n, int l, int r, int i, ll j)
	{
		if(r < i || j < l) return 0;
		if(i <= l && r <= j) return ST[n];

		return op(qry(2*n,l,(l+r)/2,i,j), qry(2*n+1,(l+r)/2+1,r,i,j));
	}
	void upd(int i, ll v)
	{
		return upd(1,0,N-1,i,v);
	}
	void upd(int n, int l, int r, int i, ll v)
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




