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

unordered_map<ll, ll> mp;



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
    ll n, B, k, x;
    cin >> n >> B >> k >> x;
    for(int i = 0; i < n; i++)
    {
        ll a;
        cin >> a;
        mp[a]++;
    }
   
    Mat A(x, x);
    for(int i = 0; i < x; i++)
        for(int j = 0; j < x; j++)
            A[i][j] = 0;
        
    for(int i = 0; i < x; i++)
    {
        for(auto it : mp)
        {
            ll y = (i * 10 + it.first) % x;
            A[y][i] += it.second;
        }
    }

        
    


   
    A = expmat(A, B-1);
    Mat b(x, 1);
    for(int i = 0; i < x; i++)
        b[i][0] = 0;

    for(auto it : mp) b[(it.first % x)][0] += it.second;

   
    b = A * b;

    


    cout << b[k][0]%MOD << "\n";
    return 0;
}