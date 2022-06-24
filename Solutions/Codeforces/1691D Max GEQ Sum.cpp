#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e16
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back

struct Node
{
	//maxPrefixSum, maxSuffixSum, Totalsum, maxSubarraySum
	ll mxP, mxS, sum, subSum;
    Node()
    {
       mxP = mxS = sum = subSum = -INF;
    }
	Node merge(Node r)
	{
		Node p;
		p.mxP = max(mxP, sum + r.mxP);
		p.mxS = max(r.mxS, r.sum + mxS);
		p.sum = sum + r.sum;
		p.subSum = max({subSum, r.subSum, mxS + r.mxP});
		return p;
	}
	void upd(ll v)
	{
		mxP = mxS = sum = subSum = v;
	}
    void nul()
    {
        mxP = mxS = subSum = -INF;
        sum = 0;
    }
};



struct SegmentTree
{
	vector<Node> ST;
	ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, Node());
		bd(1,0,N-1,A);
	}
	void bd(ll n, ll l, ll r, vl &A)
	{
		if(l == r)
		{
			ST[n].upd(A[l]);
			return;
		}

		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
	Node qry(ll i, ll j)
	{
		return qry(1,0,N-1,i,j);
	}
	Node qry(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) 
        {
            Node p;
            p.nul();
            return p;
        }

		if(i <= l && r <= j) return ST[n];

		return qry(2*n,l,(l+r)/2,i,j).merge(qry(2*n+1,(l+r)/2+1,r,i,j));
	}

	void upd(ll i, ll v)
	{
		return upd(1,0,N-1,i,v);
	}
	void upd(ll n, ll l, ll r, ll i, ll v)
	{

		if(i < l || r < i) return;

		if(l == r)
		{
			ST[n].upd(v);
			return;
		}
		upd(2*n,l,(l+r)/2,i,v);
		upd(2*n+1,(l+r)/2+1,r,i,v);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
};
//https://codeforces.com/problemset/problem/1691/D
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
	ll t;
	cin >> t;
	while(t--)
	{
		ll n, x;
        cin >> n;
        vp c;
        ll ac = 0, prev = -1;
        bool o = 1;

        ll sum = 0, maxi = -INF;

        for(int i = 0; i < n; i++)
        {
            cin >> x;
            c.pb({x, i});
        }
        sort(ALL(c));
        vl in(n, -1e10);
        SegmentTree ST(in);
        for(int i = 0; i < n; i++)
        {  
            ST.upd(c[i].second, c[i].first);
            if(ST.qry(0, n-1).subSum > c[i].first) o = 0;
            
        }
        cout << (o ? "YES\n" : "NO\n");
	}

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
