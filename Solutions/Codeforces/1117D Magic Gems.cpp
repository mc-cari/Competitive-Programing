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

ll MOD = 1e9 + 7;

struct Mat {
    vector<vector<ll>> vec;
    Mat(): vec(1, vector<ll>(1, 0)) {}
    Mat(int n): vec(n, vector<ll>(n) ) {}
    Mat(int n, int m): vec(n, vector<ll>(m) ) {}
    vector<ll> &operator[](int f){ return vec[f]; }
    const vector<ll> &operator[](int f) const { return vec[f]; }
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


int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

    ll n, m;
    cin >> n >> m;

    Mat A(m+1, m+1);
    for(int i = 0; i < m+1; i++)
        for(int j = 0; j < m+1; j++)
            A[i][j] = 0;
    A[0][0] = 1;
    A[0][m-1] = 1;

    for(int i = 1; i < m+1; i++)
        A[i][i-1] = 1;

    A = expmat(A, n);

    Mat b(m+1, 1);
    for(int i = 0; i < m+1; i++)
        b[i][0] = 0;
    b[0][0] = 1;
    b = A * b;

    cout << b[0][0] << "\n";


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}