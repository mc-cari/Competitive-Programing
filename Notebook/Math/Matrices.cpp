

#include "../Header.cpp"

/*
matrix A: transitions Axb
vector b(rows, 1): base case of dp
Represents last |b| states of dp

F_n
...
F2
F1
*/

// a^p = a*p mod P
// if a % p == 0 return 0

// to calculate p, can use p mod (P-1)
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
    rep(i, n) rep(j, t) rep(k, m)
        ans[i][j] = (ans[i][j] + A[i][k] * B[k][j] % MOD) % MOD;
    return ans;
}

Mat expmat(Mat A, ll e){
    int n = A.size();
    Mat Ans(n); rep(i, n) Ans[i][i] = 1;
    while(e){
        if(e&1) Ans = Ans*A;
        A = A*A; e >>= 1;
    }
    return Ans;
}

ll Fibo(ll n) {
    Mat V0(1, 2), T(2);
    V0[0] = {1, 1};
    T[0] = {0, 1}; T[1] = {1, 1};
    Mat V = V0*expmat(T, n);
    return V[0][0];
}