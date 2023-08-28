#include "../Header.cpp"

int joseph(int n,int m){
    int Result=0;
    for(int i=1;i<=n;i++){
        Result=(Result+m-1)%i+1;
    }
    return(Result);
}
int joseph(int n,int m){
    vl a(n+1, 0);
    //see eliminated
    bool o = 1;
    for(int i = 0; i < n/2; i++){
        a[i+1] = (a[i] + m-1)%(n-i);
        if(a[i+1] < n/2){
            o = 0;
            break;
        }
    }
}
// if k = 2
// move first significant bit to right
int joseph(ll n){
    ll bit = 62;
    while(!(n & (1 << bit))){
        bit--;
    }
    n &= ~(1 << bit);
    return 1 + (n << 1);
}

// matching in DAG gives min number of paths to cover all nodes
// Dilword
// matching in transitive DAG gives max independent set

// primes in a n size range n / log(n)

// nim game
// a_1 ^ a_2 ^ ... ^ a_n = 0: player 1 lose

// nim variation: remove stones from [0, k] piles
// a_1 ^_k+1 a_2 ^_k+1 ... ^_k+1 a_n = 0: player 1 lose
// ^_k+1 = xor mod (k+1) k+1 bits = 0 mod (k+1)
// sum of pairs
// a*b + b*c + c*a
//(a + b + c + d)^2 - (a^2 + b^2 + c^2)

// valor{x} = (x, 0)
//combinar((s_1, p_1), (s_2, p_2)) = ((s_1 + s_2),(p_1 + p_2 + s_1 * s_2))

// sum of subconj
// 1 + a + b + c + a*b + b*c + c*a + a*b*c
//(1 + a)*(1 + b)*(1 + c)

// valor{x} = 1 + x
//combinar(a, b) = a*b

// x >= y -> x mod y < x/2  counting decimals

/*Para un arbol de tamaño N, solo hay un arbol para cada divisor(N)
de tamaño divisor(N) que lo puede armar solo consigo mismo

Para hashear un arbol se usan parentesis, el hash es distinto para cada root,
hay que ordenar los hijos antes de hashear



everyone loses their hats all at once, and each person puts on a random hat;
in expectation, how many people get their own hats back? 
The probability that the each person gets their own hat is 1/N, 
and then by linearity of expectation,
the total number of instances of someone getting their own hat is 1/N*N=1.

expeted value to two people will get their original hat : 1/2
for 3: 1/3

*/

// Modular sum optimization
if (R >= MOD) R -= MOD;


/*
euler cycle
all vertex with even degree


hamiltonian cycle
d(v) >= n/2 vertex degree


exact partition  O(3^(m/3)) O(2^(m/2))
m(4) sets and n(3) objects
101 -
010 -
110
011

for each i in n:
    choose a row with bit i on
    erase all rows with bit i on
    continue
*/


// convex hull of max  max(X, Y)^(2/3) points in recatangle (0, 0) (X, Y)
