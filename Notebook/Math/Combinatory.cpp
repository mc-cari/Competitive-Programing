#include "../Header.cpp"

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

F[0] = 1; repx(i, 1, MAXN) F[i] = F[i-1]*i %M;
INV[1] = 1; repx(i, 2, MAXN) INV[i] = M - (ll)(M/i)*INV[M%i]%M;
FI[0] = 1; repx(i, 1, MAXN) FI[i] = FI[i-1]*INV[i] %M;


// combinatory
ll Comb(ll n, ll k){
    if(n < k) return 0;
    return F[n]*FI[k] %M *FI[n-k] %M;
}

// combinatury precalc
ll C[MAXN][MAXK];
// ...
rep(i, MAXN){
    C[i][0] = 1; if(i < MAXN) C[i][i] = 1;
    repx(j, 1, min(i, (int)MAXK))
        C[i][j] = (C[i-1][j-1] + C[i-1][j])%M;
}


// divide a elements into b segments = C[a-1][b-1]
// each segment has at least 1 element

//Wilson theorem
//(p-1)! mod p = -1 if p prime

//https://cp-algorithms.com/algebra/factorial-modulo.html#multiplicity-of-p

// n! mod p with p prime and ignore multiples of p
int factmod(int n, int p) {
    vector<int> f(p);
    f[0] = 1;
    for (int i = 1; i < p; i++)
        f[i] = f[i-1] * i % p;

    int res = 1;
    while (n > 1) {
        if ((n/p) % 2)
            res = p - res;
        res = res * f[n%p] % p;
        n /= p;
    }
    return res;
}

// number of times p divides n! = v_p, n! % p*v_p = 0
int multiplicity_factorial(int n, int p) {
    int count = 0;
    do {
        n /= p;
        count += n;
    } while (n);
    return count;
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
