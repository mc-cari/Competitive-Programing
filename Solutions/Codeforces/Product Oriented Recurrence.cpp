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
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

ll MOD = 1e9+7-1;


struct Mat {
    vector<vl> vec;
    Mat(): vec(1, vl(1, 0)) {}
    Mat(int n): vec(n, vl(n) ) {}
    Mat(int n, int m): vec(n, vl(m, 0) ) {}
    vl &operator[](int f){ return vec[f]; }
    const vl &operator[](int f) const { return vec[f]; }
    int size() const { return vec.size(); }
};

Mat operator *(Mat A, Mat B) {
    int n = A.size(), m = A[0].size(), t = B[0].size();
    Mat ans(n, t);
    for(int i = 0; i < n; i++) for(int j = 0; j < t; j++) for(int k = 0; k < m; k++)
        ans[i][j] = (ans[i][j] + A[i][k] * B[k][j] % MOD) % MOD;
    return ans;
}

Mat expmat(Mat A, ll e){
    int n = A.size();
    Mat Ans(n); for(int i = 0; i < n; i++) Ans[i][i] = 1;
    while(e){
        if(e&1) Ans = Ans*A;
        A = A*A; e >>= 1;
    }
    return Ans;
}

const int M = 1e9+7;
// binary exponent 
ll expmod(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b %M;
        b = b*b %M; e >>= 1;
    }
    return ans;
}


int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);


	ll n, f1, f2, f3, c;
	cin >> n >> f1 >> f2 >> f3 >> c;


	Mat A(3, 3), B(5, 5);
	A[0][0] = 1;
	A[0][1] = 1;
	A[0][2] = 1;
	A[1][0] = 1;
	A[2][1] = 1;
	B[0][0] = 1;
	B[0][1] = 1;
	B[0][2] = 1;
	B[0][3] = 2;
	B[0][4] = -6;
	B[1][0] = 1;
	B[2][1] = 1;
	B[3][3] = 1;
	B[3][4] = 1;
	B[4][4] = 1;

	/* B:
	Fn
	Fn-1
	Fn-2
	i
	1
	*/

	A = expmat(A, n - 3);
	B = expmat(B, n - 3);
	Mat F1(3, 1), F2(3, 1), F3(3, 1), C(5, 1);
	F1[2][0] = 1;
	F2[1][0] = 1;
	F3[0][0] = 1;
	C[3][0] = 4;
	C[4][0] = 1;

	F1 = A*F1;
	F2 = A*F2;
	F3 = A*F3;
	C = B*C;

	ll ans = expmod(f1, F1[0][0]);
	ans = (ans * expmod(f2, F2[0][0])) % M;
	ans = (ans * expmod(f3, F3[0][0])) % M;
	ans = (ans * expmod(c, C[0][0])) % M;
	cout << ans << "\n";

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
