#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/contest/1417/problem/F

struct UF{
    vl p,r;
    ll conjuntos=0;
    UF(ll n)//cambiar cuando no es int
    {
        conjuntos = n;
        for(ll i=0;i<n;i++)
        {
            p.push_back(i);
            r.push_back(0);
        }
    }
    ll find(ll x)
        {return p[x] = p[x] == x ? x : find(p[x]);}
    void join(ll x,ll y)
    {
        x=find(x);
        y=find(y);
        if(x!=y)
        {
            conjuntos--;
            if(r[x]>=r[y])
            {
                if(r[x]==r[y]) r[x]++;
                p[y]=x;
            }
            else p[x]=y;
        }
    }
};
struct SegmentTree
{
	vp ST;
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
			ST[n]={A[r], l};
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		ST[n] = max(ST[2*n], ST[2*n+1]);
	}
	pll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}
	pll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return {-1,-1};

		if(i <= l && r <= j) return ST[n];

		return max(query(2*n,l,(l+r)/2,i,j), query(2*n+1,(l+r)/2+1,r,i,j));
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
			ST[n].first = v;
			return;
		}

		update(2*n,l,(l+r)/2,i,v);
		update(2*n+1,(l+r)/2+1,r,i,v);

		ST[n] = max(ST[2*n], ST[2*n+1]);
	}
};

ll cont = -1, n;
vl L(400005, -1), R(400005, -1), ID(400005, -1);
vl arr;
void dfs(vector<vl>& g, vl& vis, vl& c, ll in, ll id)
{
    if(!vis[in]){
        vis[in] = 1;
        cont++;
        if(in >= n)
          arr.push_back(-1);
        else
          arr.push_back(c[in]);
        L[in] = cont;
        ID[in] = id;
        for(int i = 0; i < g[in].size(); i++)
        {   
            if(!vis[g[in][i]])
              dfs(g, vis, c, g[in][i], id);
        }
        R[in] = cont;
    }

}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  ll m, q, x, y;
  cin >> n >> m >> q;
  vl c;
  for(int i = 0; i < n; i++)
  {
    cin >> x;
    c.push_back(x);
  }
  vp ar;
  vl visar(m, 0);
  for(int i = 0; i < m; i++)
  {
    cin >> x >> y;
    ar.push_back({x-1, y-1});
  }
  vp Q;
  for(int i = 0; i < q; i++)
  {
    cin >> x >> y;
    Q.push_back({x, y-1});
    if(x == 2)
      visar[y-1] = 1;
  }
  for(int i = 0; i < m; i++)
  {
    if(!visar[i])Q.push_back({2, i});
  }
  
  UF uf(400005);
  ll in = n;
  vector<vl> g(400005, vl(0));
  vl que(Q.size(), -1);
  for(int i = Q.size()-1; i >= 0; i--)
  {
    if(Q[i].first == 2)
    {
      ll x = uf.find(ar[Q[i].second].first), y = uf.find(ar[Q[i].second].second);
      if(x == y)
      continue;
      
      g[in].push_back(x);
      g[in].push_back(y);
      uf.p[x] = in;
      uf.p[y] = in;
      in++;
    }
    else
    {
      ll x = uf.find(Q[i].second);
      que[i] = x;
    }
  }

  set<ll> nod;
  for(int i = 0; i < n; i++)
  {
    nod.insert(uf.find(i));
  }
  ll id = 0;
  vector<SegmentTree> STs;
  for(auto it:nod)
  {
    arr.clear();
    vl vis(in, 0);
    cont = -1;
    dfs(g, vis, c, it, id);
    SegmentTree ST(arr);
    STs.push_back(ST);
    id++;
  }
  for(int i = 0; i < Q.size(); i++)
  {
    if(Q[i].first == 1)
    {
      ll id, v;
      tie(v, id) = STs[ID[que[i]]].query(L[que[i]], R[que[i]]);
      cout<<v<<"\n";
      STs[ID[que[i]]].update(id, 0);
    }
  }

}
