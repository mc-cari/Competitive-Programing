#include "../Header.cpp"

struct Node
{
	
	ll mn, mn2, cmn, mx, mx2, cmx;
	ll sum;
	Node()
	{
			mn = mn2 = LLONG_MAX;
      mx = mx2 = LLONG_MIN;
			sum = cmn = cmx = 0;
	}
	Node merge(Node r)
	{
		Node p;
		p.sum = sum + r.sum;
		if(r.mn < mn)
		{
			p.mn2 = min(mn, r.mn2);
			p.mn = r.mn;
			p.cmn = r.cmn;
		}
		else if(r.mn == mn)
		{
			p.cmn = cmn + r.cmn;
			p.mn = mn;
			p.mn2 = min(p.mn2, r.mn2);
		}
		else if(mn < r.mn)
		{
			p.mn2 = min(mn2, r.mn);
			p.mn = mn;
			p.cmn = cmn; 
		}

    if(r.mx > mx)
    {
      p.mx2 = max(mx, r.mx2);
      p.mx = r.mx;
      p.cmx = r.cmx;
    }
    else if(r.mx == mx)
    {
      p.cmx = cmx + r.cmx;
      p.mx = mx;
      p.mx2 = max(p.mx2, r.mx2);
    }
    else if(mx > r.mx)
    {
      p.mx2 = max(mx2, r.mx);
      p.mx = mx;
      p.cmx = cmx; 
    }
    
		return p;
	}
	void upd(ll v)
	{
		cmn = cmx = 1;
		mn = mx = v;
		sum = v;
	}
};


struct SegmentTree
{
	vector<Node> ST;
	ll N;
	vl Lazy, Lazymx, Lazymn, LazySet;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, Node());
		Lazy.resize(4*N+5, 0);
		Lazymx.resize(4*N+5, LLONG_MIN);
    Lazymn.resize(4*N+5, LLONG_MAX);
		LazySet.resize(4*N+5, LLONG_MIN);
		bd(1,0,N-1,A);
	}
	void bd(ll n, ll l, ll r, vl &A)
	{
		if(l == r)
		{
			ST[n].upd(A[l]);
			//cout << "n " << n << " " << ST[n].mn << " " << ST[n].mn2 << " " << ST[n].sum << " " << ST[n].cmn << "\n";
			return;
		}
		
		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);

		ST[n] = ST[2*n].merge(ST[2*n+1]);

		//cout << "n " << l << " "<<r << " " << ST[n].mn << " " << ST[n].mn2 << " " << ST[n].sum << " " << ST[n].cmn << "\n";
	}
	void up(ll n, ll l, ll r)
	{
			//set
			if(LazySet[n] != LLONG_MIN)
			{
				ST[n].mn = LazySet[n];
				ST[n].mn2 = LLONG_MAX;
				ST[n].sum = (r-l+1)*LazySet[n];
				ST[n].cmn = r-l+1;
        ST[n].mx2 = LLONG_MIN;
        ST[n].mx = LazySet[n];
        ST[n].cmx = r-l+1;

				//cout << "nlazy " << l << "--" << r << " " << ST[n].mn << " " << ST[n].mn2 << " " << ST[n].sum << " " << ST[n].cmn << "\n";
			}
		 	else{
				ST[n].sum += (r-l+1)*Lazy[n];
				ST[n].mn += Lazy[n];
        ST[n].mx += Lazy[n];

				if(ST[n].mn2 != LLONG_MAX)ST[n].mn2 += Lazy[n];
        if(ST[n].mx2 != LLONG_MIN)ST[n].mx2 += Lazy[n];
			}
			
			// mx op
			push_min(n, Lazymx[n], l == r);
      // mn op
      push_max(n, Lazymn[n], l == r);

			//cout << l << "--" << r << " " << Lazy[n] << " " << Lazymx[n] << " " << ST[n].sum << endl;

			if(l != r)
			{
          Lazy[n*2] += Lazy[n];
          Lazy[n*2+1] += Lazy[n];

          Lazymx[n*2] = ST[n].mn;
          Lazymx[n*2+1] = ST[n].mn;
  
          Lazymn[n*2] = ST[n].mx;
          Lazymn[n*2+1] = ST[n].mx;
          if(LazySet[n] != LLONG_MIN)
          {
              LazySet[n*2] = LazySet[n];
              LazySet[n*2+1] = LazySet[n];
          }

			}
			Lazy[n] = 0;
			Lazymx[n] = LLONG_MIN;
      Lazymn[n] = LLONG_MAX;
			LazySet[n] = LLONG_MIN;
	}
  // op max
	void push_min(ll n, ll v, bool l){
		if(v <= ST[n].mn) return;
		ST[n].sum += (v-ST[n].mn)*ST[n].cmn;
		ST[n].mn = v;

		if (l) {
			ST[n].mx = ST[n].mn;
		} 
		else if (v >= ST[n].mx) {
			ST[n].mx = v;
		} else if (v > ST[n].mx2) {
			ST[n].mx2 = v;
		}
	}
  // op min
  void push_max(ll n, ll v, bool l){
    if(v >= ST[n].mx) return;
    ST[n].sum += (v-ST[n].mx)*ST[n].cmx;
    ST[n].mx = v;

		if (l) {
			ST[n].mn = ST[n].mx;
		}
		else if (v <= ST[n].mn) {
			ST[n].mn = v;
		} else if (v < ST[n].mn2) {
			ST[n].mn2 = v;
		}
	
  }
  // a[i]=max(a[i], v)
	void updmx(ll n, ll l, ll r, ll i, ll j, ll v)
	{
		up(n,l,r);
		if(l > j || r < i || v <= ST[n].mn) return;
		if(i <= l && r <= j && v < ST[n].mn2)
		{
			push_min(n,v,l==r);
			up(n,l,r);
			return;
		}
		updmx(2*n,l,(l+r)/2,i,j,v);
		updmx(2*n+1,(l+r)/2+1,r,i,j,v);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
  // a[i]=min(a[i], v)
  void updmn(ll n, ll l, ll r, ll i, ll j, ll v)
  {
    up(n,l,r);
    if(l > j || r < i || v >= ST[n].mx) return;
    if(i <= l && r <= j && v > ST[n].mx2)
    {
      push_max(n,v,l==r);
      up(n,l,r);
      return;
    }
    updmn(2*n,l,(l+r)/2,i,j,v);
    updmn(2*n+1,(l+r)/2+1,r,i,j,v);

    ST[n] = ST[2*n].merge(ST[2*n+1]);
  }
	Node qry(ll n, ll l, ll r, ll i, ll j)
	{
		
		if(r < i || j < l)
		{
			Node p;
			return p;
		}
		up(n,l,r);

		if(i <= l && r <= j) {
			//cout <<l <<" "<<r<< "* " << ST[n].sum<<"\n";
			return ST[n];
		}
		return qry(2*n,l,(l+r)/2,i,j).merge(qry(2*n+1,(l+r)/2+1,r,i,j));
	} 
	void upd_add(ll n, ll l, ll r, ll i, ll j, ll v)
	{
		up(n,l,r);
		if(l > j || r < i) return;

		if(i <= l && r <= j)
		{
			//cout << l << " " << r << " "<<ST[n].sum << "\n";
			Lazy[n] += v;
			up(n, l, r);
			return;
		}
		upd_add(2*n,l,(l+r)/2,i,j,v);
		upd_add(2*n+1,(l+r)/2+1,r,i,j,v);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
	void upd_set(ll n, ll l, ll r, ll i, ll j, ll v)
	{
		up(n,l,r);
		if(l > j || r < i) return;

		if(i <= l && r <= j)
		{
			//cout << l << " " << r << " "<<ST[n].sum << "\n";
			LazySet[n] = v;
			up(n, l, r);
			return;
		}
		upd_set(2*n,l,(l+r)/2,i,j,v);
		upd_set(2*n+1,(l+r)/2+1,r,i,j,v);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
  Node qry(ll i, ll j){return qry(1,0,N-1,i,j);}
  void updmx(ll i, ll j, ll v){return updmx(1,0,N-1,i,j,v);}
  void updmn(ll i, ll j, ll v){return updmn(1,0,N-1,i,j,v);}
  void upd_add(ll i, ll j, ll v){return upd_add(1,0,N-1,i,j,v);}
  void upd_set(ll i, ll j, ll v){return upd_set(1,0,N-1,i,j,v);}
};

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));


	vl c = {0, 0, 0, 0, 0, 0}, d = c;
	SegmentTree ST(c);

	rep(i, c.size()){
		cout << ST.qry(i, i).sum << " ";
	}
	cout << endl;

	ST.upd_add(2, 3, 2);
	cout << ST.qry(2, 3).sum << endl;
	rep(i, c.size()){
		cout << ST.qry(i, i).sum << " ";
	}
	cout << endl;


	ST.updmx(0, 3, 3);
	cout << ST.qry(0, 3).sum << endl;
	rep(i, c.size()){
		cout << ST.qry(i, i).sum << " ";
	}
	cout << endl;

	ST.updmx(3, 5, 1);
	cout << ST.qry(3, 5).sum << endl;
	rep(i, c.size()){
		cout << ST.qry(i, i).sum << " ";
	}
	cout << endl;

	ST.upd_add(0, 5, -3);
	cout << ST.qry(0, 5).sum << endl;
	rep(i, c.size()){
		cout << ST.qry(i, i).sum << " ";
	}
	cout << endl;



	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}