#include "../Header.cpp"

// pre overflow
ll mul(ll x, ll y) { if (x > MX / y) return MX; return x * y; }
ll sums(ll x, ll y) { if (MX - x < y) return MX; return x + y; }



const int N = 1e5 + 10, LOG_A = 31;

ll basis[LOG_A], sz;

// O(N * LOG), base que produce el máximo
void insertVector(int mask) {
	for (ll i = LOG_A - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
            sz++;
			return;
		}

		mask ^= basis[i];
	}
}


vector<vl > memo (5001,vl (50,-1));
ll Com (ll n,ll r,ll p) //Coef binomial modulo p(primo)
{
    if(r<0||r>n) return 0;
    if(r==0||n==r)return 1;
    if(n>=p)
    {
        return Com(n/p,r/p,p)*Com(n%p,r%p,p)%p;
    }
    if(memo[n][r]==-1)
    {
        memo[n][r]=(Com(n-1,r-1,p)+Com(n-1,r,p))%p;
    }

    return memo[n][r];
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

// When M is prime
ll invmod(ll a){ return expmod(a, M-2); }

//inv modular factoriales
const ll MAXN = 1e5 + 1;
ll F[MAXN], INV[MAXN], FI[MAXN];
// ...
F[0] = 1; for(ll i = 1; i < MAXN; i++) F[i] = F[i-1]*i %M;
INV[1] = 1; for(ll i = 2; i < MAXN; i++) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
FI[0] = 1; for(ll i = 1; i < MAXN; i++) FI[i] = FI[i-1]*INV[i] %M;

// factoriales n = 1e18, primo chico
ll F[MAXN];
struct Fact{
    ll s, k;   
    ´0
    1l8 ml-+9
    8{j1|    24}
    Fa*2/ct(ll  2 ol-
    .
    ]n){if(n < M){ s = F[n]; k = 0; return; }
        ll d = n / M;
        *this = Fact(d);
        s = s*F[n%M] %M * (d%2 ? M-1 : 1) %M;
        k += d;
    }
};

// combinatoria
ll Comb(ll n, ll k){
    if(n < k) return 0;
    return F[n]*FI[k] %M *FI[n-k] %M;
}

// combinatoria precalculo
ll C[MAXN][MAXK];
// ...
for(int i = 0; i < MAXN; i++)
    C[i][0] = 1; if(i < MAXK) C[i][i] = 1;
    for(int j = 1; j < min(i, MAXK); j++)
        C[i][j] = (C[i-1][j-1] + C[i-1][j])%M;


// combinatoria precalculo acotado
vector<vector<ll>> C;
// ...
scanf(“%d %d”, &N, &K); C.resize(N, vector<ll>(K));
forn(i, N){
    C[i][0] = 1; if(i < K) C[i][i] = 1;
    forr(j, 1, min(i, K))
        C[i][j] = (C[i-1][j-1] + C[i-1][j])%M;
}


// combinatoria n = 1e18, primo chico
// lucas
const int M = 3005;
int C[M][M];
// ...
ll lucas(ll n, ll k, int p){
    ll ans = 1;
    while(n + k){
        ans = (ans * C[n%M][k%M]) % M;
        n /= M; k /= M;
    }
    return ans;
}

// inclusion, exclusion
ll ans = 0;
forr(bitmask, 1, (1<<n)){
    // bitmask srepresenta la interseccion actual
    bool resta = __builtin_popcount(bitmask)%2;
    ans = (ans + (resta ? 1 : M-1)*cuenta(bitmask) %M) %M;
}

// numeros catalan

/*
• Cantidad de formas de ubicar correctamente 𝒏 pares de paréntesis.
• Número de árboles binarios con 𝒏 nodos.
• Número de árboles binarios completos con 𝒏 + 𝟏 hojas.
• Cantidad de triangulaciones de un polígono convexo de 𝒏 + 𝟐 lados.

*/

ll CAT[MAXN];
// ...
CAT[0] = CAT[1] = 1;
forr(i, 2, MAXN){
    CAT[i] = 0;
    forn(k, i)
    C   AT[i]=(CAT[i]+CAT[k]*CAT[i-1-k]%M)%M;
}

ll F[MAXN], INV[MAXN], FI[MAXN];
ll Cat(int n){
    return F[2*n] *FI[n+1]%M *FI[n]%M;
}

// Numeros stirling

ll Stirling[MAXN][MAXN];
// ...
forr(i, 1, MAXN)Stirling[i][1] = 1;
forr(i, 2, MAXN)Stirling[1][i] = 0;
forr(i, 2, MAXN)forr(j, 2, MAXN){
    Stirling[i][j] =
    (Stirling[i-1][j-1] + j*Stirling[i-1][j]%MOD) %MOD;
}


// Numeros bell

ll Stirling[MAXN][MAXN], Bell[MAXN];
// ...
forn(i, MAXN){
    Bell[i] = 0;
    forn(j, MAXN)
        Bell[i] = (Bell[i] + Stirling[i][j]) %MOD;
}

// Matrices


// Matrix exp

/*
matrix A: transitions Axb
vector b(rows, 1): base case of dp
Represents last |b| states of dp


*/

struct Mat {
    vector<vl> vec;
    Mat(): vec(1, vl(1, 0)) {}
    Mat(int n): vec(n, vl(n) ) {}
    Mat(int n, int m): vec(n, vl(m) ) {}
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

ll Fibo(ll n) {
    Mat V0(1, 2), T(2);
    V0[0] = {1, 1};
    T[0] = {0, 1}; T[1] = {1, 1};
    Mat V = V0*expmat(T, n);
    return V[0][0];
}

// C function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y);

// Function to find modulo inverse of a
void modInverse(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist";
    else
    {
        // m is added to handle negative x
        int res = (x%m + m) % m;
        cout << "Modular multiplicative inverse is " << res;
    }
}

// C function for extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

//https://github.com/PabloMessina/Competitive-Programming-Material/blob/master/Mathematics/chinese_remainder_theorem.cpp

inline ll mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }
inline ll mul(ll x, ll y, ll m) { return (x * y) % m; }
inline ll add(ll x, ll y, ll m) { return (x + y) % m; }

// extended euclidean algorithm
// finds g, x, y such that
//    a * x + b * y = g = GCD(a,b)
ll gcdext(ll a, ll b, ll& x, ll& y) {
    ll r2, x2, y2, r1, x1, y1, r0, x0, y0, q;
    r2 = a, x2 = 1, y2 = 0;
    r1 = b, x1 = 0, y1 = 1;
    while (r1) {
        q = r2 / r1;
        r0 = r2 % r1;
        x0 = x2 - q * x1;
        y0 = y2 - q * y1;
        r2 = r1, x2 = x1, y2 = y1;
        r1 = r0, x1 = x0, y1 = y0;        
    }
    ll g = r2; x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y; // make sure g > 0
    // for debugging (in case you think you might have bugs)
    // assert (g == a * x + b * y);
    // assert (g == __gcd(abs(a),abs(b)));
    return g;
}

// ==============================================
// CRT for a system of 2 modular linear equations
// ==============================================
// We want to find X such that:
//   1) x = r1 (mod m1)
//   2) x = r2 (mod m2)
// The solution is given by:
//    sol = r1 + m1 * (r2-r1)/g * x' (mod LCM(m1,m2))
// where x' comes from
//   m1 * x' + m2 * y' = g = GCD(m1,m2)
//   where x' and y' are the values found by extended euclidean algorithm (gcdext)
// Useful references:
//   https://codeforces.com/blog/entry/61290
//   https://forthright48.com/chinese-remainder-theorem-part-1-coprime-moduli
//   https://forthright48.com/chinese-remainder-theorem-part-2-non-coprime-moduli
// ** Note: this solution works if lcm(m1,m2) fits in a long long (64 bits)
pair<ll,ll> CRT(ll r1, ll m1, ll r2, ll m2) {
    ll g, x, y; g = gcdext(m1, m2, x, y);
    if ((r1 - r2) % g != 0) return {-1, -1}; // no solution
    ll z = m2/g;
    ll lcm = m1 * z;
    ll sol = add(mod(r1, lcm), m1*mul(mod(x,z),mod((r2-r1)/g,z),z), lcm);
    // for debugging (in case you think you might have bugs)
    // assert (0 <= sol and sol < lcm);
    // assert (sol % m1 == r1 % m1);
    // assert (sol % m2 == r2 % m2);
    return {sol, lcm}; // solution + lcm(m1,m2)
}

// ==============================================
// CRT for a system of N modular linear equations
// ==============================================
//  Args:
//      r = array of remainders
//      m = array of modules
//      n = length of both arrays
//  Output: 
//      a pair {X, lcm} where X is the solution of the sytemm
//          X = r[i] (mod m[i]) for i = 0 ... n-1
//      and lcm = LCM(m[0], m[1], ..., m[n-1])
//      if there is no solution, the output is {-1, -1}
// ** Note: this solution works if LCM(m[0],...,m[n-1]) fits in a long long (64 bits)
#define rep(i,a,b) for (int i=a; i<b; ++i)
pair<ll,ll> CRT(ll* r, ll* m, int n) {
    ll r1 = r[0], m1 = m[0];
    rep(i,1,n) {
        ll r2 = r[i], m2 = m[i];
        ll g, x, y; g = gcdext(m1, m2, x, y);
        if ((r1 - r2) % g != 0) return {-1, -1}; // no solution
        ll z = m2/g;
        ll lcm = m1 * z;
        ll sol = add(mod(r1, lcm), m1*mul(mod(x,z),mod((r2-r1)/g,z),z), lcm);
        r1 = sol;
        m1 = lcm;
    }
    // for debugging (in case you think you might have bugs)
    // assert (0 <= r1 and r1 < m1);
    // rep(i,0,n-1) assert (r1 % m[i] == r[i]);
    return {r1, m1};
}


//grundy
int tag[n*n];
int mex(int id)
{
    int ans = 0;
    while(tag[ans] == id) ++ans;
    return ans;
}

ll cn = 0;
for(int i = 0; i < n; i++)
{
    for(int j = 0; j < n; j++)
    {
        ll id = ++cn;
        //abajo
        for(int k = i - 1; k >= 0; k--)
            tag[grundy[k][j]] ] = id;
        
        //izquierda
        for(int k = j - 1; k >= 0; k--)
            tag[grundy[i][k]] ] = id;

        // diagonal
        for(int k = 1; k <= min(i, j); k++)
            tag[grundy[i-k][j-k]] ] = id;
        grundy[i][j] = mex(id);
    }
}