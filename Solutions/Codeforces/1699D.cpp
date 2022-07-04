#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
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

//https://codeforces.com/contest/1699/problem/D

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);


	ll t;
	cin >> t;
	while (t--)
	{
		ll n, x;
		cin >> n;
		vl c;

		for(int i = 0; i < n; i++)
		{
			cin >> x;
			c.pb(x-1);
		}
		vl memo(n+2, 0);
		for(int i = 0; i <= n; i++)
		{

			vl dom(n, 0);
			ll maxi = 0; 

			for(int j = i; j <= n; j++)
			{
				if(j != i)
				{
					dom[c[j-1]]++;
					if(dom[c[j-1]] > maxi) maxi = dom[c[j-1]];
				}
				if((j - i) % 2 == 0 && maxi <= (j - i) / 2)
				{
					
					if(i == 0)
					{
						if(i != 0 && memo[i] == 0) continue;  
						memo[j+1] = max(memo[j+1], memo[i] + 1);

					}
					else 
					{
						if(j != n && c[i-1] != c[j])continue;
						if(i != 0 && memo[i] == 0) continue;  
						memo[j+1] = max(memo[j+1], memo[i] + 1);
					}
					
				}
			}
		}
		
		cout << max(0, memo[n+1]-1) << "\n";
		

	}
	
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
