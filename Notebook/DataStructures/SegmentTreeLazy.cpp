#include "../Header.cpp"

struct Node
{
  ll mini, cont; 
  Node(ll val, ll cont)
  {
    this->mini = val;
    this->cont = cont;
  }
  Node()
  {
    mini = 1e18;
    cont = 0;
  }

  Node operator + (const Node& p) const { 
    return Node(min(mini, p.mini), cont + p.cont); 
  }
};

ll ans = 0;

struct SegmentTree
{
	vector<Node> ST;
  vl Lazy;
	int N; ll Nul = 0;
	SegmentTree(vector<ll> &A)
	{
		N = A.size();
		ST.resize(4*N+5, Node());
		Lazy.resize(4*N+5,Nul);
		bd(1,0,N-1,A);
	}
	void up(int n, int l, int r)
	{
			ST[n].mini += Lazy[n];
			if(l != r)
			{
					Lazy[n*2] += Lazy[n];
					Lazy[n*2+1] += Lazy[n];
			}
			Lazy[n] = Nul;
	}
	void bd(int n, int l, int r, vl &A)
	{
		if(l == r)
		{
			ST[n] = Node(A[r], 1);
			return;
		}

		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);
		ST[n] = ST[2*n] + ST[2*n+1];
	}

	Node qry(int n, int l, int r, int i, int j)
	{
		if(r < i || j < l ) return Node();
    if(Lazy[n] != Nul) up(n,l,r);
		if(i <= l && r <= j) return ST[n];
		return qry(2*n,l,(l+r)/2,i,j) + qry(2*n+1,(l+r)/2+1,r,i,j);
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
		ST[n] = ST[2*n] + ST[2*n+1];
	}

  void search(int n, int l, int r, int j, ll v)
	{
		if(Lazy[n] != Nul) up(n,l,r);
    if(l > j || ST[n].mini > v) return;

    if(l == r)
    {
      ans += ST[n].mini;
      ST[n] = Node();
      if(Lazy[n] != Nul) up(n, l, r);
			return;
    }

	  search(2*n,l,(l+r)/2,j,v);
		search(2*n+1,(l+r)/2+1,r,j,v);

		ST[n] = ST[2*n] + ST[2*n+1];
	}

  Node qry(int i, int j)
	  {return qry(1,0,N-1,i,j);}
  void upd(int i, int j, ll v)
	  {return upd(1,0,N-1,i,j,v);}
  void search(int j, ll v)
	  {return search(1,0,N-1,j,v);}
};
