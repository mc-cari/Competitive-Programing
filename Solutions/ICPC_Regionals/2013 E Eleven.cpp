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

//https://www.urionlinejudge.com.br/judge/es/problems/view/1494

const ll MAXN = 1e4 + 1, M = 1e9 + 7;
ll F[MAXN], INV[MAXN], FI[MAXN];

ll Comb(ll n, ll k){
    if(n < k) return 0;
    return F[n]*FI[k] %M *FI[n-k] %M;
}
ll memo[20][60][60][24];
ll dp(ll d, ll p, ll i, ll x, vl& c)
{

	if(d == 10)
	{
		if(x == 0) return 1;
		else return 0;
	}
	if(memo[d][p][i][x] != -1) return memo[d][p][i][x];
	ll ans = 0;
	for(ll j = 0; j <= c[d]; j++)
	{	
		if(j <= p && c[d] - j <= i)
			ans = (((Comb(p, j) * Comb(i, c[d] - j)) % M) * dp(d + 1, p - j, i - c[d] + j, (11 + ((x - d * (2 * j - c[d])) % 11)) % 11, c) + ans) % M;
	}
	return memo[d][p][i][x] = ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	string s;
	F[0] = 1; for(ll i = 1; i < MAXN; i++) F[i] = F[i-1]*i %M;
	INV[1] = 1; for(ll i = 2; i < MAXN; i++) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
	FI[0] = 1; for(ll i = 1; i < MAXN; i++) FI[i] = FI[i-1]*INV[i] %M;
	while(cin >> s)
	{
		memset(memo, -1, sizeof(memo));
		vl c(10, 0);
		for(auto it : s)
		{
			c[it - '0']++;
		}
		ll l = s.size();
		ll ans = dp(0, l - l / 2, l / 2, 0, c);
		if(c[0] > 0)
		{
			memset(memo, -1, sizeof(memo));
			c[0]--;
			ans += M - dp(0, l - l / 2 - 1, l / 2, 0, c);
			ans %= M;
		}
		cout<<ans<<"\n";
	}
	

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
