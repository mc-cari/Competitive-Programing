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


double R;
void draw_circle_perimeter(double r, vector<vl> & p){
	for(ll x = -r; x <= r; x++)
	{
		ll y = round(sqrt(r * r - 1.0*x * x)) ;
		p[x + R][y + R] = 1;
		p[x + R][-y + R] = 1;
		p[y + R][x + R] = 1;
		p[-y + R][x + R] = 1;

	}
	return;
}
void draw_circle_filled(vector<vl> & p){
	for(ll x = -R; x <= R; x++)
	{
		for(ll y = -R; y <= R; y++)
		{
			if(round(sqrt(1.0*x*x + 1.0*y*y)) <=R)
				p[x + R][y + R] = 1;
		}
	}
	return;
}
void draw_circle_filled_wrong(vector<vl> & p)
{
	for(ll r = 0; r <= R; r++)
	{
		draw_circle_perimeter(r, p);
	}
}


int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);

  
	ll t;
	cin >> t;
	for(int T = 1; T <= t; T++)
	{
		cin >> R;
		vector<vl> A(2*R+1, vl(2*R+1, 0)), B(2*R+1, vl(2*R+1, 0));
		draw_circle_filled(A);
		draw_circle_filled_wrong(B);
		ll ans = 0;
		for(int x = 0; x <= 2*R; x++)
		{
			for(int y = 0; y <= 2*R; y++)
			{
				if(A[x][y] != B[x][y])
					ans++;
				
			}
		}
		cout << "Case #" << T << ": " << ans << "\n";
	}
		
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}