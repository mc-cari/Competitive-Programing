//https://dmoj.ca/problem/coci09c5p3

#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)


ll W, L, N;
bool check(vl &upper1, vl &lower1, vl &upper2, vl &lower2){
	rep(i, L)
	{
		if(W - upper1[i] - lower1[i] != W - upper2[i] - lower2[i]) return false;

		if(i < L-1) if(upper1[i+1] - upper1[i] != upper2[i+1] - upper2[i]) return false;
	}

	return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
		cin >> W >> L >> N;

		vector<vl> uppers(N, vl(L)), lowers(N, vl(L));

		rep(i, N){
			rep(j, L) cin >> uppers[i][j];
			rep(j, L) cin >> lowers[i][j];
		}
		ll ans = 0;

		rep(i, N){
			bool o = 0;
			rep(j, i)
			{
				o |= check(uppers[i], lowers[i], uppers[j], lowers[j]);
				reverse(ALL(uppers[i]));
				reverse(ALL(lowers[i]));
				o |= check(uppers[i], lowers[i], uppers[j], lowers[j]);
				o |= check(lowers[i], uppers[i], uppers[j], lowers[j]);
				reverse(ALL(uppers[i]));
				reverse(ALL(lowers[i]));
				o |= check(lowers[i], uppers[i], uppers[j], lowers[j]);
			}
			if(!o)ans++;
		}
		cout << ans << "\n";
}
