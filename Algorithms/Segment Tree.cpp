#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())

/*
beats
node(suma, max, max2, cant_max)

*/

struct SegmentTree
{
	vl ST;
	ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.resize(4*N);
		build(1,0,N-1,A);
	}
	void build(ll n, ll l, ll r, vl &A)
	{
		if(l==r)
		{
			ST[n]=A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		ST[n] = ST[2*n]+ST[2*n+1];
	}
	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}
	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return 0;

		if(i <= l && r <= j) return ST[n];

		return (query(2*n,l,(l+r)/2,i,j)+query(2*n+1,(l+r)/2+1,r,i,j));
	}

	void update(ll i, ll v)
	{
		return update(1,0,N-1,i,v);
	}
	void update(ll n, ll l, ll r, ll i, ll v)
	{

		if(i < l || r < i) return;

		if(l == r)
		{
			ST[n] = v;
			return;
		}

		update(2*n,l,(l+r)/2,i,v);
		update(2*n+1,(l+r)/2+1,r,i,v);

		ST[n] = ST[2*n] + ST[2*n+1];
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n,x,y,p=1;
	string z;
	vl A;
	while(cin>>n)
	{
	if(n==0)break;
	if(p!=1)cout<<"\n";
	A.clear();
	for (ll i=0;i<n;i++)
	{
		cin>>x;
		A.push_back(x);
	}
	cout<<"Case "<<p<<":\n";
	SegmentTree ST(A);
	while(cin>>z)
	{
		if(z=="END")break;
		else if(z=="S")
		{
			cin>>x>>y;
			ST.update(x-1,y);
		}
		else
		{
			cin>>x>>y;
			cout<<ST.query(x-1,y-1)<<endl;
		}
	}

	p++;
	}
	return 0;
}
