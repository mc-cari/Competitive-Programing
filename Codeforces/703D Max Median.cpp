#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e9
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
 
//https://codeforces.com/contest/1486/problem/D
 
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
		ST[n] = max(ST[2*n],ST[2*n+1]);
	}
 
	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}
	ll query(ll n, ll l, ll r, ll i, ll j)
	{
 
		if(r < i || j < l ) return -INF;
 
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
            up(n, l, r);
            return;
        }
        if(i <= l && r <= j)
        {
            Lazy[n] += v;
            up(n, l, r);
            return;
        }
        up(n,l,r);
 
		update(2*n,l,(l+r)/2,i,j,v);
		update(2*n+1,(l+r)/2+1,r,i,j,v);
 
		ST[n] = max(ST[2*n],ST[2*n+1]);
	}
};
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
 
    ll n, k, x;
    vl c, d, aux;
    cin >> n >> k;
 
    for(int i = 0; i < n; i++){
        cin >> x;
        d.push_back(x);
        c.push_back(x);
    }
    sort(ALL(d));
    UNIQUE(d);
 
    ll pivot = (d.size()+1)/2 -1;
    d.push_back(INF);
    for(int i = 0; i < n; i++)
    {
        if(c[i] < d[pivot])aux.push_back(-1);
        else aux.push_back(1);
        if(i > 0)aux.back() += aux[i-1];
    }
    SegmentTree ST(aux);
    /*cout << pivot<<": "<<d[pivot]<<"\n";
    for(int i = 0; i < n; i++)
    {
            cout<<ST.query(i, i)<<" ";
    }cout << "\n\n";*/
    
    ll l = 0 ,r = d.size() ,p , res = -1;
    while(l <= r)
    {
        p = (l + r) / 2;
 
        if(pivot > p)
        {
            for(int i = 0; i < n; i++)
            {
                if(c[i] >= d[p] && c[i] < d[pivot]) ST.update(i, n-1, 2);
            }
        }
        else if(pivot < p)
        {
            for(int i = 0; i < n; i++)
            {
                if(c[i] >= d[pivot] && c[i] < d[p]) ST.update(i, n-1, -2);
            }
        }
        
        pivot = p;
        bool o = 0;
        for(int i = 0; i < n; i++)
        {
            if(i + k - 1 >= n)break;
            ll aux2 = 0;
            if(i != 0)aux2 = ST.query(i-1, i-1);
            if(ST.query(i + k - 1, n-1) - aux2> 0) o = 1;
        }
        /*cout<<p<<": "<<d[p]<<" "<<o<<"\n";
        for(int i = 0; i < n; i++)
        {
            cout<<ST.query(i, i)<<" ";
        }cout << "\n";*/
 
        if(o)
        {
            res = p;
            l = p+1;
        }
        else r = p-1;
    }
    cout <<d[res]<<"\n";
 
    
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
