#include "../Header.cpp"



struct SegmentTree
{
	vector<ll> ST, Lazy;
	int N; ll Nul = 0;
	SegmentTree(vector<ll> &A)
	{
		N = A.size();
		ST.resize(4*N+5,0);
		Lazy.resize(4*N+5,Nul);

		bd(1,0,N-1,A);
	}
	void up(int n, int l, int r)
	{
			ST[n] += Lazy[n];
			if(l != r)
			{
					Lazy[n*2] += Lazy[n];
					Lazy[n*2+1] += Lazy[n];
			}
			Lazy[n] = Nul;
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
	ll qry(int n, int l, int r, int i, int j)
	{
		if(r < i || j < l ) return Nul;
    if(Lazy[n] != Nul) up(n,l,r);
		if(i <= l && r <= j) return ST[n];
		return op(qry(2*n,l,(l+r)/2,i,j), qry(2*n+1,(l+r)/2+1,r,i,j));
	}
	void upd(int i, int j, ll v)
	{
		return upd(1,0,N-1,i,j,v);
	}
	void upd(int n, int l, int r, int i, int j, ll v)
	{
		if(Lazy[n] != Nul) up(n,l,r);
		if(l > j || r < i) return;

		if(i <= l && r <= j)
		{
			Lazy[n] += v;
			if(Lazy[n] != Nul) up(n, l, r);
			return;
		}

		upd(2*n,l,(l+r)/2,i,j,v);
		upd(2*n+1,(l+r)/2+1,r,i,j,v);
		ST[n] = op(ST[2*n], ST[2*n+1]);
	}
};


