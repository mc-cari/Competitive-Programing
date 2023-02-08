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
//https://www.acmicpc.net/problem/17794
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
        ST[n] = max(ST[n],Lazy[n]);
        if(l != r)
        {
            Lazy[n*2] = max(Lazy[n*2],Lazy[n]);
            Lazy[n*2+1] = max(Lazy[2*n+1],Lazy[n]);
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


		ST[n] = max(ST[2*n],ST[2*n+1]);
	}

	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}


	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l ) return Nul;

    up(n,l,r);


		if(i <= l && r <= j) return ST[n];


		return max(query(2*n,l,(l+r)/2,i,j),query(2*n+1,(l+r)/2+1,r,i,j));
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
            Lazy[n]=max(Lazy[n],v);
            up(n,l,r);
            return;
        }
        up(n,l,r);

		update(2*n,l,(l+r)/2,i,j,v);
		update(2*n+1,(l+r)/2+1,r,i,j,v);

		ST[n] = max(ST[2*n],ST[2*n+1]);
	}
};

int main() {

  ll s,c,a,b;
  vector<pll>coins;
  vector<tuple<ll, ll, ll> >slots;
  cin>>s;
  vl A(s,0);
  SegmentTree ST(A);
  for(int i=0; i<s;i++)
  {
    cin>>a>>b;
    slots.push_back(make_tuple(b,a,i));
  }
  sort(ALLR(slots));
  cin>>c;
  for(int i=0; i<c;i++)
  {
    cin>>a>>b;
    coins.push_back({b,a});
  }
  sort(ALL(coins));
  ll sum=0;
  for(int i=0;i<c;i++)
  {
    while(!slots.empty() && get<0>(slots.back()) <= coins[i].first)
    {
      ST.update(get<2>(slots.back()),s-1,get<1>(slots.back()));
      slots.pop_back();
    }
    ll l=0,r=s-1,p, res=s;
    while(l<=r)
    {
        p=(l+r)/2;
        
        if(ST.query(p,p)>=coins[i].second)
        {
          r=p-1;
          res = min(res,p+1);
        }
        else l=p+1;
    }

    sum+=res;

  }
  cout<<sum<<"\n";
}
