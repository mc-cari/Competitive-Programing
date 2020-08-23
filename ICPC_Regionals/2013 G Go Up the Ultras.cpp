#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://www.urionlinejudge.com.br/judge/es/problems/view/1496

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

		ST[n] = min(ST[2*n],ST[2*n+1]);
	}
	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}
	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return INF;

		if(i <= l && r <= j) return ST[n];

		return min(query(2*n,l,(l+r)/2,i,j),query(2*n+1,(l+r)/2+1,r,i,j));
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

		ST[n] = min(ST[2*n],ST[2*n+1]);
	}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    while(cin >> n)
    {
      ll x;
      vl c, l, r;
      for(int i = 0; i < n; i++)
      {
        cin >> x;
        c.push_back(x);
      }
      SegmentTree ST(c);
      stack<pll > prev;
      for(int i = 0; i < n; i++)
      {
        while(!prev.empty() && prev.top().first <= c[i])prev.pop();
        if(prev.empty())
        {
          l.push_back(-1);
        }
        else
        {
          l.push_back(prev.top().second);
        }
        
        prev.push({c[i], i});
        
      }
      while(!prev.empty())prev.pop();

      for(int i = n-1; i >= 0; i--)
      {
        while(!prev.empty() && prev.top().first <= c[i])prev.pop();
        if(prev.empty())
        {
          r.push_back(-1);
        }
        else
        {
          r.push_back(prev.top().second);
        }
        prev.push({c[i], i});
        
      }
      reverse(ALL(r));
      ll ans = 0;
      for(int i = 0; i < n; i++)
      {
        
        bool L = 0, R = 0;
        if(l[i] == -1 && c[i] >= 150000)L = 1;
        else if(c[i] - ST.query(l[i], i) >= 150000) L = 1;
        if(r[i] == -1 && c[i] >= 150000)R = 1;
        else if(c[i] - ST.query(i, r[i]) >= 150000) R = 1;
        //cout<<"\n"<<i<<" "<<R<<" "<<r[i]<<" "<<ST.query(i, r[i])<<"\n";
        if(L && R)
        {
          if(ans > 0)cout<<" ";
          cout<<i+1;
          ans++;
        }
      }
      cout<<"\n";

    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
