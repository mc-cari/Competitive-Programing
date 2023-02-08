#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
 
 // https://www.urionlinejudge.com.br/judge/es/problems/view/1491
 
ll Largo, Largo2;
string P;
struct SegmentTree
{
	vector<ll> Min, Max;
  vector<bool> Lazy;
	ll N;
  ll Nul = 0;
	SegmentTree(vector<ll> &A)
	{
		N = A.size();
		Lazy.resize(4*N+5,Nul);
    Min.resize(4*N+5,-1);
    Max.resize(4*N+5,-1);
    buildM(1,0,N-1,A);
    buildMM(1,0,N-1,A);
	}
  void up(ll n, ll l, ll r)
  {
      if(Lazy[n])
      {
        if(Min[n]!=-1)Min[n] = Largo - Min[n];
        if(Max[n]!=-1)Max[n] = Largo - Max[n];
        swap(Max[n], Min[n]);
        if(l != r)
        {
            Lazy[n*2] = !Lazy[n*2];
            Lazy[n*2+1] = !Lazy[n*2+1];
        }
        else
        {
          if(islower(P[l])) P[l] = toupper(P[l]);
          else P[l] = tolower(P[l]);
        }
        Lazy[n] = Nul;
      }
  }
  void buildM(ll n, ll l, ll r, vector<ll> &A)
	{

		if(l == r)
		{
			Max[n] = A[r];
			return;
		}

		buildM(2*n,l,(l+r)/2,A);
		buildM(2*n+1,(l+r)/2+1,r,A);

    Max[n] = max(Max[2*n], Max[2*n+1]);
	}
  void buildMM(ll n, ll l, ll r, vector<ll> &A)
	{

		if(l == r)
		{
			Min[n] = A[r];
			return;
		}

		buildMM(2*n,l,(l+r)/2,A);
		buildMM(2*n+1,(l+r)/2+1,r,A);
    ll S1 = Min[2*n], S2 = Min[2*n+1];
    if(S1 == -1) Min[n] =  S2;
    else if(S2 == -1) Min[n] = S1;
    else Min[n] = min(S1, S2);
	}

	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}

	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < l||r < i || j < l) return -1;

    up(n,l,r);


		if(i <= l && r <= j) return Max[n];

    return max(query(2*n,l,(l+r)/2,i,j), query(2*n+1,(l+r)/2+1,r,i,j));
	}
  void queryS(ll i, ll j)
	{
		return queryS(1,0,N-1,i,j);
	}

	void queryS(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return;

    up(n,l,r);

		if(i <= l && r <= j) return;

		queryS(2*n,l,(l+r)/2,i,j);
    queryS(2*n+1,(l+r)/2+1,r,i,j);
	}

	void update(ll i,ll j)
	{
		return update(1,0,N-1,i,j);
	}

	void update(ll n, ll l, ll r, ll i, ll j)
	{
    
		if(l > j || r < i)
    {
        up(n,l,r);
        return;
    }
    if(i<=l&&r<=j)
    {
        Lazy[n] = !Lazy[n];
        up(n,l,r);
        return;
    }
    up(n,l,r);
		update(2*n,l,(l+r)/2,i,j);
		update(2*n+1,(l+r)/2+1,r,i,j);
    

    Max[n] = max(Max[2*n], Max[2*n+1]);
    ll S1 = Min[2*n], S2 = Min[2*n+1];
    if(S1 == -1) Min[n] =  S2;
    else if(S2 == -1) Min[n] = S1;
    else Min[n] = min(S1, S2);
	}
  void updateP(ll i, ll v)
	{
		return updateP(1,0,N-1,i, v);
	}

	void updateP(ll n, ll l, ll r, ll i, ll v)
	{

		if(i < l || r < i)
    {
      up(n,l,r);
      return;
    }
    
		if(l == r)
		{
      Max[n] = v;
      Min[n] = v;
      up(n,l,r);
			return;
		}
    up(n,l,r);
    
		updateP(2*n,l,(l+r)/2,i,v);
		updateP(2*n+1,(l+r)/2+1,r,i,v);

    Max[n] = max(Max[2*n], Max[2*n+1]);
    ll S1 = Min[2*n], S2 = Min[2*n+1];
    if(S1 == -1) Min[n] =  S2;
    else if(S2 == -1) Min[n] = S1;
    else Min[n] = min(S1, S2);
	}
};


ll match(string& T, ll in)//mismatch
{
  if(in + Largo - 1 >= Largo2)return -1;
  ll m = 0;
  for(int i = 0; i < Largo; i++)
  {
    if(T[i] != P[in + i])m++;
    if(tolower(T[i]) != tolower(P[in + i])) return -1;
  }
  return m;

}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll N;
  string T;
  while(cin >> N >> T)
  {
    cin >> P;
    vl A;
    Largo2 = P.size();
    Largo = T.size();
    for(int i = 0; i < Largo2; i++)
    {
      A.push_back(match(T, i));
    }
    SegmentTree ST(A);
        

    for(int i = 0; i < N; i++)
    {
      int l, r;
      cin >> l >> r;
      l--; r--;
      cout<<ST.query(l, r - (Largo - 1))<<"\n";
      ST.update(l, r);
      for(int j = l - Largo; j <= l + Largo + 1; j++)
      {
        if(j < 0 || j >= Largo2)continue;
        ST.queryS(j,j);
      }
      for(int j = r - Largo; j <= r + Largo + 1; j++)
      {
        if(j < 0 || j >= Largo2)continue;
        ST.queryS(j,j);
      }


      for(int j = l - Largo; j < l; j++)
      {
        if (j < 0|| j >= Largo2 || A[j] == -1)continue;

        A[j] = match(T, j);
        ST.updateP(j, A[j]);
      }
      for(int j = r - Largo; j <= r; j++)
      {
        if (j < 0|| j >= Largo2 || A[j] == -1)continue;
        A[j] = match(T, j);
        ST.updateP(j, A[j]);
      }
    }
  }

    return 0;
}

