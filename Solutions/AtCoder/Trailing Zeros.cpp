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


int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ll n;
	vl c, d;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		ll x;
		cin >> x;
		c.push_back(x);
	}
	ll num = (1LL << c[0]), max_bit = c[0];
	for(int i = 1; i < n; i++)
	{
		//cout << num << "\n";
		if(c[i] == c[i -1]){
			num += (1LL << (c[i]+1));
		}
		else if(c[i] >= c[i - 1])
		{
			max_bit += c[i] - c[i - 1];
			for(ll j = 0; j < c[i]; j++)
			{
				if((1LL << j) & num) num -= (1LL << j);
			}
			ll aux = (1LL << (c[i]));
			
			num += (1LL << (c[i]));
			
			num |= (1LL << (c[i]));
			
		}
		else

			num += (1LL << c[i]);

	}
	cout << num << "\n";


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}