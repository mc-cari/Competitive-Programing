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

//https://codeforces.com/gym/103185/problem/L

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

	
	ll n, x, s, d;
	cin >> n >> x;
	vp c;
	for(int i = 0; i < n; i++) 
	{
		cin >> s >> d;
		c.push_back({s, d});
	}
	sort(ALL(c));
	ll mini = INF, ans;
	for(int i = 0; i <= 480; i++)
	{
		ll in = 0, T = i, cont = 0;
		while(in < n )
		{
			while (T < c[in].first) T += x;

			while(T <= c[in].first + c[in].second){
				cont++;
				T += x;
			}
			in++;

			
			
		}
		if(cont < mini)
		{
			mini = cont;
			ans = i;
		}
	}
	cout << ans << " " << mini << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
