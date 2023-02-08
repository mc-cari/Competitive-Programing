#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
const ll inf = 1e14;

//https://www.codechef.com/problems/SPREAD

struct SegmentTree
{
	vector<ll> ST,Lazy;
	ll N;
  ll Nul = 0;
	SegmentTree(vector<ll> &A)
	{
		N = A.size();
		ST.resize(4*N+5,0);
		Lazy.resize(4*N+5,Nul);

		build(1,0,N-1,A);
	}
    void up(ll n, ll l, ll r)
    {
        ST[n] += Lazy[n];
        if(l != r)
        {
            Lazy[n*2] += Lazy[n];
            Lazy[n*2+1] += Lazy[n];
        }
        Lazy[n] = Nul;
    }
	void build(ll n, ll l, ll r, vector<ll> &A)
	{

		if(l == r)
		{
			ST[n] = A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);


		ST[n] = (ST[2*n]+ST[2*n+1]);
	}

	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}


	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l ) return 0;

    up(n,l,r);


		if(i <= l && r <= j) return ST[n];

		return (query(2*n,l,(l+r)/2,i,j)+query(2*n+1,(l+r)/2+1,r,i,j));
	}

	void update(ll i,ll j, ll v)
	{
		return update(1,0,N-1,i,j,v);
	}

	void update(ll n, ll l, ll r, ll i, ll j, ll v)
	{

		if(l > j || r < i)
        {
            up(n,l,r);
            return;
        }
        if(i<=l&&r<=j)
        {
            Lazy[n]+=v;
            up(n,l,r);
            return;
        }
        up(n,l,r);

		update(2*n,l,(l+r)/2,i,j,v);
		update(2*n+1,(l+r)/2+1,r,i,j,v);


		ST[n] = (ST[2*n]+ST[2*n+1]);
	}
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n,m,c,p,u,v,k;
  cin>>n>>m>>c;
  vl A(n,c);
  SegmentTree ST(A);
  for(int i=0;i<m;i++)
  {
    char s;
    cin>>s;
    if(s=='Q')
    {
      cin>>p;
      cout<<ST.query(p-1,p-1)<<"\n";
    }
    else
    {
      cin>>u>>v>>k;
      u--;v--;
      ST.update(u,v,k);
    }
    
  }
}
