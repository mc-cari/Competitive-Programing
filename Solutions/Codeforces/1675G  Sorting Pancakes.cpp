#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
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
#define pb push_back

// https://codeforces.com/contest/1675/problem/G
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, m;
	vl ac(1, 0), panc_ac(1, 0); // prefix sum of pancake pos

	cin >> n >> m;

	for(int i = 0; i < n; i++)
	{
		ll x;
		cin >> x;
		ac.pb(x + ac.back());
		
		for(int j = 0; j < x; j++)
		{
			panc_ac.pb(panc_ac.back() + i);
			
		}
		

	}
	vector<vector<vl>> memo(n+1, vector<vl>(m+1, vl(m+1, INF)));

	for(int j = 0; j <= m; j++)
	{
		if(ac[1] >= j) memo[0][j][j] = ac[1] - j; // move right
		else memo[0][j][j] = panc_ac[j]; // move pancakes [0:j] to pos 0
	}
	for(int j = m-1; j >= 0; j--)
		for(int k = j; k <=m; k++)
			memo[0][j][k] = min(memo[0][j][k], memo[0][j+1][k]);

	for(int i = 1; i < n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int k = j; k <= m; k++)
			{
				ll add = 0;
				if(ac[i+1] >= k) add = ac[i+1] - k; //move unused to right
				else{
					ll lend = min((ll)j, k - ac[i+1]);
					add = panc_ac[k] - panc_ac[k - lend] - i * lend;
				}
				memo[i][j][k] = memo[i - 1][j][k - j] + add;
			}
		}

		for(int j = m-1; j >= 0; j--)
			for(int k = j; k <=m; k++)
				memo[i][j][k] = min(memo[i][j][k], memo[i][j+1][k]);
	}
	cout << memo[n-1][0][m] << "\n";

	
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
