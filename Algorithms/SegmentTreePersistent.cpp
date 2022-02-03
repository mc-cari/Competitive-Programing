#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
struct SegmentTree
{
	vector<vl> ST, Leftv, Rightv;
	ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.resize(4*N, vl());
		Leftv.resize(4*N, vl(1, 0)); // all conected to version 0
		Rightv.resize(4*N, vl(1, 0));
		build(1,0,N-1,A);
	}
	void build(ll n, ll l, ll r, vl &A)
	{
		if(l==r)
		{
			ST[n].push_back(A[r]);
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		ST[n].push_back(ST[2*n][0] + ST[2*n+1][0]);
	}
	ll query(ll i, ll j, ll vs)
	{
		return query(1,0,N-1,i,j, vs);
	}
	ll query(ll n, ll l, ll r, ll i, ll j, ll vs)
	{

		if(r < i || j < l) return 0;

		if(i <= l && r <= j) return ST[n][vs];

		return (query(2*n,l,(l+r)/2,i,j, Leftv[n][vs]) + query(2*n+1,(l+r)/2+1,r,i,j, Rightv[n][vs]));
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
			ST[n].push_back(v);
			return;
		}

		update(2*n,l,(l+r)/2,i,v);
		update(2*n+1,(l+r)/2+1,r,i,v);

		ST[n].push_back(ST[2*n].back() + ST[2*n+1].back());
		Leftv[n].push_back(ST[2*n].size()-1);
		Rightv[n].push_back(ST[2*n+1].size()-1);
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	vl a = {1, 2, 3, 4, 5};
	
	SegmentTree ST(a);

	

	ST.update(4, 1);
	ST.update(2, 10);


    cout << "In version 1 , query(0,4) : "; 
    cout << ST.query(0, 4, 1) << endl; 
  
    cout << "In version 2 , query(3,4) : "; 
    cout << ST.query(3, 4, 2) << endl; 
  
    cout << "In version 0 , query(0,3) : "; 
    cout << ST.query(0, 4, 0) << endl; 
	return 0;
}
