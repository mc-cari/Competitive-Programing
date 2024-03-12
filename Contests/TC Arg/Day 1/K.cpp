#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

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

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vl c(n);
  rep(i, n) cin >> c[i];

  SegmentTree ST(c);

  rep(i, n){
    ans = 0;
    ll t;
    cin >> t;

    ST.search(i, t);
    ST.upd(0, i, -t);

    cout << ans + ST.qry(0, i).cont * t << " ";
  }
}