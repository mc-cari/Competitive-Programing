#include "../Header.cpp"

struct SegmentTree
{
	vector<vl> ST; vector<vi> Leftv, Rightv;
	int N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.resize(4*N, vl());
		// ST.resize(4*N, vl(1, 0)); whitout build, init with 0s
		Leftv.resize(4*N, vi(1, 0)); // all conected to version 0
		Rightv.resize(4*N, vi(1, 0));
		bd(1,0,N-1,A);
	}
	ll op(ll x, ll y) { return min(x,y); }
	void bd(int n, int l, int r, vl &A)
	{
		if(l==r)
		{
			ST[n].push_back(A[r]);
			return;
		}

		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);

		ST[n].push_back(op(ST[2*n][0], ST[2*n+1][0]));
	}
	ll qry(int i, int j, int vs)
	{
		return qry(1,0,N-1,i,j, vs);
	}
	ll qry(int n, int l, int r, int i, int j, int vs)
	{

		if(r < i || j < l) return 0;

		if(i <= l && r <= j) return ST[n][vs];

		return op(qry(2*n,l,(l+r)/2,i,j, Leftv[n][vs]), qry(2*n+1,(l+r)/2+1,r,i,j, Rightv[n][vs]));
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
			ST[n].push_back(v); // ST[n].push_back(v + ST[n].back()) add
			return;
		}

		upd(2*n,l,(l+r)/2,i,v);
		upd(2*n+1,(l+r)/2+1,r,i,v);

		ST[n].push_back(op(ST[2*n].back(), ST[2*n+1].back()));
		Leftv[n].push_back(ST[2*n].size()-1);
		Rightv[n].push_back(ST[2*n+1].size()-1);
	}
};