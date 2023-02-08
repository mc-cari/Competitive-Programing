#include "../Header.cpp"
#include "UnionFind.cpp"

// M log M (log M from UF)
struct DinC
{
	vector<vp> DC;
	ll T; UF uf;
	DinC(ll times, ll n)
	{
		T = times;
		DC.assign(4*T, vp());
		uf = UF(n);
	}
	void qry()
	{
		qry(1, 0, T-1);
	}
	void qry(ll n, ll l, ll r)
	{

		for(auto it : DC[n]) uf.join(it.first, it.second);

		if(l == r) // process time l
		{
			for(auto it : ord[l])
			{
				
				ll x1 = uf.find(it.first);
				ll x2 = uf.find(it.second);
				ans += uf.sz[x1] * uf.sz[x2];
			}
			
		}
		else{
			qry(2*n,l,(l+r)/2);
			qry(2*n+1,(l+r)/2+1,r);
		}

		for(auto it : DC[n]) uf.rollback();
	}
	void upd(ll i,ll j, pll v)
	{
		return upd(1, 0, T-1, i, j, v);
	}
	void upd(ll n, ll l, ll r, ll i, ll j, pll v)
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