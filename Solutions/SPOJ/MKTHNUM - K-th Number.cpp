#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/MKTHNUM/

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
	ll n, m, x;
    vl c;
    vp d;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x);
        d.push_back({x, i});
    }
    sort(ALL(d));
	
    vl aux (n, 0);
	SegmentTree ST(aux);

	for(int i = 0; i < n; i++)
    {
        ST.update(d[i].second, 1);
    }
    
    for(int i = 0; i < m; i++){
        ll I, J, K;
        cin >> I >> J >> K;
        I--; J--;
        ll l = 1 ,r = n,p , res = -1;
        while(l <= r)
        {
            p = (l + r) / 2;
            if(ST.query(I, J, p) < K)l = p+1;
            else 
            {
                r = p-1;
                res = p;
            }
        }
        cout << d[res-1].first << "\n";
    }



    
	return 0;
}
