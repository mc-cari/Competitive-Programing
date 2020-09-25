#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/KOPC12G/

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

		ST[n] = ST[2*n]+ST[2*n+1];
	}
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll t;
  cin >> t;
  while(t--)
  {
      ll n, q;
      cin >> n >> q;
      vector<SegmentTree> STs;
      for(int i = 0; i < n; i++)
      {
          string s;
          vl c;
          cin >> s;
          for(auto it: s)
          {
              c.push_back(it - 'A' + 1);
          }
          SegmentTree ST(c);
          STs.push_back(ST);
      }
      while(q--)
      {
          ll r, x1, x2, y1, y2;
          string s;
          cin >> r;
          if(r == 0)
          {
              cin >> x1 >> y1 >> s;
              if(x1 == 1)
              {
                  for(int i = 0; i < n; i++)
                  {
                      STs[i].update(y1, s[i] - 'A' + 1);
                  }
              }
              else
              {
                  for(int i = 0; i < n; i++)
                  {
                      STs[y1].update(i, s[i] - 'A' + 1);
                  }
              }
              
          }
          else
          {
              cin >> x1 >> y1 >> x2 >> y2;
              ll ans = 0;
              for(int i = x1; i <= x2; i++)
              {
                  ans += STs[i].query(y1, y2);
              }
              cout << ans << "\n";
          }
          
      }
  }
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
