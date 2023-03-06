#include "../Header.cpp"

// pre overflow
ll mul(ll x, ll y) { if (x > MX / y) return MX; return x * y; }
ll sums(ll x, ll y) { if (MX - x < y) return MX; return x + y; }

const int N = 1e5 + 10, LOG_A = 31;

ll basis[LOG_A], sz;

// O(N * LOG), base that produces the maximum
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

// inclusion, exclusion
ll ans = 0;
forr(bitmask, 1, (1<<n)){
    // bitmask srepresenta la interseccion actual
    bool resta = __builtin_popcount(bitmask)%2;
    ans = (ans + (resta ? 1 : M-1)*cuenta(bitmask) %M) %M;
}

// Catalan number

/*
• Number of ways to place 𝒏 pairs of parentheses correctly.
• Number of binary trees with 𝒏 nodes.
• Number of full binary trees with 𝒏 + 𝟏 leaves.
• Number of ways to triangulate a convex 𝒏 + 𝟐 sided polygon.
*/

ll CAT[MAXN];
// ...
CAT[0] = CAT[1] = 1;
repx(i, 2, MAXN){
    CAT[i] = 0;
    rep(k, i)
        CAT[i]=(CAT[i]+CAT[k]*CAT[i-1-k]%M)%M;
}
ll F[MAXN], INV[MAXN], FI[MAXN];
ll Cat(int n){
    return F[2*n] *FI[n+1]%M *FI[n]%M;
}
// Stirling numbers

// number of ways to partition a set of n elements into k nonempty subsets

ll Stirling[MAXN][MAXN];
// ...
repx(i, 1, MAXN)Stirling[i][1] = 1;
repx(i, 2, MAXN)Stirling[1][i] = 0;
repx(i, 2, MAXN)forr(j, 2, MAXN){
    Stirling[i][j] =
    (Stirling[i-1][j-1] + j*Stirling[i-1][j]%MOD) %MOD;
}

// Bell numbers

// Number of partitions of set of n elements

// a deck of n cards is shuffled by repeatedly removing the top card and reinserting it anywhere in the deck (including its original position at the top of the deck), with exactly n repetitions
// stays the same B_n ways
// Probability B_n / n^n

// nth Bell number equals the number of permutations on n items in which no three values that are in sorted order have the last two of these three consecutive
ll Stirling[MAXN][MAXN], Bell[MAXN];
// ...
forn(i, MAXN){
    Bell[i] = 0;
    forn(j, MAXN)
        Bell[i] = (Bell[i] + Stirling[i][j]) %MOD;
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

// fibonacci numbers
f_i = 1 / sqrt(5 * ((1 + sqrt(5)) / 2) ^ n - ((1 - sqrt(5)) / 2) ^ n);

// catalan numbers
a_n = 1 / (n+1) * comb(2n, n);