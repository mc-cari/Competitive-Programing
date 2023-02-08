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

https://codeforces.com/contest/121/problem/E

vl num = {4,7,44,47,74,77,444,447,474,477,744,747,774,777, 7777, 7774, 7747, 7477, 4777, 7744, 7474, 7447, 4774, 4747, 4477, 7444, 4744, 4474, 4447, 4444};

struct SegmentTree
{
  vector<ll> Lazy, in;
  vector<pll> ST;
  ll N;
  ll Nul = 0;
  SegmentTree(vector<pll>& A)
  {
    N = A.size();
    ST.resize(4*N+5,{0,0});
    Lazy.resize(4*N+5,Nul);
    in.resize(N+5, 0);

    build(1,0,N-1, A);
  }
  void up(ll n, ll l, ll r)
  {
      ST[n].first -= Lazy[n];
      if(l != r)
      {
          Lazy[n*2] += Lazy[n];
          Lazy[n*2+1] += Lazy[n];
      }
      Lazy[n] = Nul;
  }
  void build(ll n, ll l, ll r, vector<pll>& A)
  {

    if(l == r)
    {
	ST[n] = A[r];
	return;
    }

    build(2*n,l,(l+r)/2, A);
    build(2*n+1,(l+r)/2+1,r, A);

    if(ST[2*n].first == ST[2*n+1].first) ST[n] = {ST[2*n].first, ST[2*n].second + ST[2*n+1].second};
    else ST[n] = min(ST[2*n],ST[2*n+1]);
  }

  ll query(ll i, ll j)
  {
    return query(1,0,N-1,i,j);
  }


  ll query(ll n, ll l, ll r, ll i, ll j)
  {

    if(r < i || j < l ) return Nul;

    up(n,l,r);
    if(i <= l && r <= j) 
    {
      if(ST[n].first == 0) return ST[n].second;
      return 0;
    }

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
        Lazy[n] += v;
        up(n,l,r);
        
        return;
    }
    up(n,l,r);

    update(2*n,l,(l+r)/2,i,j,v);
    update(2*n+1,(l+r)/2+1,r,i,j,v);


    if(ST[2*n].first == ST[2*n+1].first) ST[n] = {ST[2*n].first, ST[2*n].second + ST[2*n+1].second};
    else ST[n] = min(ST[2*n],ST[2*n+1]);
  }

  void normalize(ll n, ll l, ll r)
  {

     up(n,l,r);

    if(ST[n].first >= 0)
    {
        return;
    }

  
    if(l == r)
    {
      while(ST[n].first < 0)
      {
        in[l]++;
        if(in[l] == num.size())
          ST[n].first = 100000;
        else
          ST[n].first += num[in[l]] - num[in[l]-1];
      }
      return;
    }

    up(n,l,r);

    normalize(2*n,l,(l+r)/2);
    normalize(2*n+1,(l+r)/2+1,r);

    up(n,l,r);

    if(ST[2*n].first == ST[2*n+1].first) ST[n] = {ST[2*n].first, ST[2*n].second + ST[2*n+1].second};
    else ST[n] = min(ST[2*n],ST[2*n+1]);

  }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    sort(ALL(num));
    ll n, m, x;
    cin >> n >> m;
    vector<pll> A;
    
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        A.push_back({num[0] - x, 1});
    }
    SegmentTree ST(A);
    while(m--)
    {
        string s;
        ll l, r, d;
        cin >> s;
        if(s == "count")
        {
          cin >> l >> r;
          ST.normalize(1,0,ST.N-1);
          cout<<ST.query(l-1, r-1)<<"\n";
        }
        else
        {
          cin >> l >> r >> d;
          ST.update(l-1, r-1, d);
        }
        
    }


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
