#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

//https://www.beecrowd.com.br/judge/es/problems/view/1356
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

vl p(1e5+5, 0);
ll P;

struct SegmentTree
{
	vl ST;
	ll N;
	SegmentTree(ll n)
	{
		N = n;
		ST.resize(4*N);

	}
	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}
	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return 0;

		if(i <= l && r <= j) return ST[n];
		
		return ((query(2*n,l,(l+r)/2,i,j) * p[max(min(j,r) - (l+r)/2, 0LL)])%P + query(2*n+1,(l+r)/2+1,r,i,j))%P;
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

		ST[n] = (ST[2*n + 1] + (ST[2*n] * p[r - (l+r)/2])%P)%P;
	}
};


int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

	ll B, L, N;
	while(cin >> B >> P >> L >> N && (B + P + L + N)){
	
		ll mul = 1;
		for(int i = 0; i < 1e5+5; i++)
		{
			p[i] = mul;
			mul *= B;
			mul %= P;
		}
		SegmentTree ST(L);
		for(int i = 0; i < N; i++)
		{
			char h;
			ll I, V, J;
			cin >> h;
			if(h == 'E')
			{
				cin >> I >> V;
				ST.update(I-1, V);
			}
			else 
			{
				cin >> I >> J;
				cout << ST.query(I-1, J-1) << "\n";
			}
		}
		cout << "-\n";
	}

	
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
