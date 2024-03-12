#include<bits/stdc++.h>
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
  ll mini, maxi; 
  Node(ll val, ll val2)
  {
    this->mini = val;
    this->maxi = val2;
  }
  Node()
  {
    mini = 1e18;
    maxi = -1;
  }

  Node operator + (const Node& p) const { 
    return Node(min(mini, p.mini), max(maxi, p.maxi)); 
  }
};
ll M = 1e9+7;
ll ans = -1;

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
            if(Lazy[n])
            {
                ST[n].mini = M - ST[n].mini;
                ST[n].maxi = M - ST[n].maxi;
                swap(ST[n].mini, ST[n].maxi);
            }

			if(l != r)
			{
					Lazy[n*2] += Lazy[n];
                    Lazy[n*2] %= 2;
					Lazy[n*2+1] += Lazy[n];
                    Lazy[n*2+1] %= 2;
			}
			Lazy[n] = 0;
	}
	void bd(int n, int l, int r, vl &A)
	{
		if(l == r)
		{
			ST[n] = Node(A[r], A[r]);
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
            Lazy[n] %= 2;
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
        if(l > j || ST[n].maxi != v || ans != -1) return;

        if(l == r)
        {
            ans = l+1;
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


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    repx(T, 1, t+1)
    {
        int n;
        cin >> n;
        
        vl c(n);
        rep(i, n)cin >> c[i];
        SegmentTree ST(c);

        int q;
        cin >> q;
        ll res = 0;

        while(q--)
        {
            int l, r;
            cin >> l >> r;
            l--; r--;

            ST.upd(l, r, 1);
            ll maxi = ST.qry(0, n-1).maxi;
            ans = -1;
            ST.search(n, maxi);
            ll day = ans;
            res += day;

        }

        cout << "Case #" << T << ": " << res << "\n";

    }
    
}