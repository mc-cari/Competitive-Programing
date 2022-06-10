#include "../Header.cpp"
#include "UnionFind.cpp"
struct DC
{
	vector<vp> DC;
	ll T; UF uf;
	SegmentTree(ll times, ll n)
	{
		T = times;
		DC.assign(4*T, vp());
		uf = UF(n);
	}
	void qry()
	{
		return upd(1, 0, N-1, 0);
	}
	void qry()
	{
		if(r < i || j < l) return;

		for(auto it : DC[n]) uf.find(it.first, it.second);

		if(l == r) // process time l
		{

		}
		qry(2*n,l,(l+r)/2);
		qry(2*n+1,(l+r)/2+1,r);

		for(auto it : DC[n]) uf.rollback()
	}
	void upd(ll i,ll j, ll v)
	{
		return upd(1, 0, N-1, i, j, v);
	}
	void upd(ll n, ll l, ll r, ll i, ll j, ll v)
	{
		if(r < i || j < l) return;
        if(i <= l && r <= j)
        {
            DC[n].pb(v);
            return;
        }
		upd(2*n,l,(l+r)/2,i,j,v);
		upd(2*n+1,(l+r)/2+1,r,i,j,v);
	}
};