#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e17
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

//https://www.acmicpc.net/problem/24607

int main(){


	ll a, b, n;
	cin >> a >> b >> n;
	ll dirx = 1, diry = 1, p = -1, q = 1, s = 0, t = 1, dxn, dxd, dyn, dyd;
	for(ll k = 0; k < n+1; k++){
		dxd = q;
		dyd = t;
		if(dirx == 1) dxn = q - p;
		else dxn = q + p;
		if(diry == 1) dyn = t - s;
		else dyn = t + s;
		if(dxn * a*dyd < dyn * b*dxd){
			if(dirx == 1){
				p = 1;
				q = 1;
				dirx = -1;
			}
			else{
				p = -1;
				q = 1;
				dirx = 1;
			}
			s = s*b*dxd + dxn*t*diry*a;
			t = t*b*dxd;
		}
		else{
			if(diry == 1){
				s = 1;
				t = 1;
				diry = -1;
			}
			else{
				s = -1;
				t = 1;
				diry = 1;
			}
			p = p*a*dyd + dyn*q*dirx*b;
			q = q*a*dyd;
		}
		ll aux = 1;
		if(p) aux = __gcd(abs(p), abs(q));
		else q = 1;
		p /= aux;
		q /= aux;

		aux = 1;
		if(s) aux = __gcd(abs(s), abs(t));
		else t = 1;
		s /= aux;
		t /= aux;
		
	}

	cout << p << " " << q << " ";

	cout << s << " " << t << "\n";
	return 0;
}
