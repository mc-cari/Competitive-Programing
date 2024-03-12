#include "../Header.cpp"

using namespace chrono;
auto start1 = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start1);
//cerr << duration.count()/1000 << "ms" << endl;

default_random_engine generator;
uniform_real_distribution<double> distribution(0,LLONG_MAX);
ll num = distribution(generator);


// files
ifstream input;
input.open("divisibility-tree.in");
input >> n;
ofstream output;
output.open("divisibility-tree.out");
output<<" ";  
output.close();

// subset sum
for i = 0 to n-1
    for mask = 0 to (1«n) - 1
        if (mask & (1«i))
            dp(mask) += dp(mask - (1«i))

// divisor sum
for p ∈ P
    for x ∈ S // Increasing order
        if (p divide a x)
            dp(x) += dp(x / p)

// hash pairs unrderedmap<pll,ll,hash_pair>
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

//propagate val in mask to all its submask
for (int i = 0; i < p; i++)
{
    for(int mask = 0; mask < (1 << p); mask++)
    {
        if((mask & (1 << i)) == 0)
            f[mask] += f[mask | (1 << i)];
        if(mask & (1 << i)) // to propagate from submasks to mask
            dp[mask] += dp[mask - (1 << i)];
    }
}

// Iterate over non empty subsets of bitmask
for(int s=m;s;s=(s-1)&m) // Decreasing order
for (int s=0;s=s-m&m;) 	 // Increasing order

// O(3^n)
rep(m, (1 << n)){
    // 2^k k: number of bits in m
    // iterates over al submasks of m in descending order of value
    for(int s = m; ; s = (s-1) & m){
        cout << s << endl;
        if(s == 0) break;
    }
}

int bit_opst(ll N,ll S)
{
    
    // Return the numbers the numbers of 1-bit in x
    int __builtin_popcount (unsigned int x)
    // Returns the number of trailing 0-bits in x. x=0 is undefined.
    int __builtin_ctz (unsigned int x)
    // Returns the number of leading 0-bits in x. x=0 is undefined.
    int __builtin_clz (unsigned int x)

    //Obtain the remainder (modulo) of S when it is divided by N (N is a power of 2)
    return S &(N -1);
    //Determine if S is a power of 2.
    return (S &( S -1)) == 0;
    //Turn oﬀ the last bit in S, e.g.S = (40)10 = (101000)2 →S = (32)10 = (100000)2.
    return S &( S -1);
    // Turn on the last zero in S, e.g.S = (41)10 = (101001)2 →S = (43)10 = (101011)2.
    return S|| (S + 1);
    // Turn oﬀ the last consecutive run of ones in S
    return S &( S + 1);
    // Turn on the last consecutive run of zeroes in S
    return S|| (S -1);
    // Turn on all bits
    return S = (1 << 62)-1;
    // multiply by 2^N
    return S<<=N;
    // Divide by 2^N
    return S>>=N;
    // Turn on the N-th bit
    return S = S||(1<<N);
    // Check if N-th bit is on
    return (S & (1 << N));
    // Turn off the N-th bit
    return S &= ~(1 << N);
    // Alternate satatus of N-th bir
    return S ^= (1 << N);
    //Value of the least significant bit on from the right
    return N = (S&(-S));
}
//count numbers with i bit set [1, n-1]
ll kol(ll n, ll i)
{
    return (n / (1ll << (i + 1))) * (1ll << i) + max((n % (1ll << (i + 1))) - (1ll << i), 0ll);
}
kol(r+1, i) - kol(l, i);

// Gradien descent
db find(db x, int dir)
{
    rep(i, 10)
    {
        db x2 = x + dir * 0.01 * der(x);
        x = x2;
    }
    while(abs(der(x)) > 0.001 )
    {
        db x2 = x + dir * 0.0001 * der(x);
        x = x2;
    }

    return x;
}



// old implemented algorithms:

int A[10000];//Set con reset O(1),Tambien con Map
int t=1;
bool fin(int x)
{
    return A[x]==t;
}
void borrar()
{
    t++;
}
void inse(int x)
{
    A[x]=t;
}

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}
int extn_gcd(int m, int n)
{
    stack<tuple<int,int,int,int> >ext_gcd;
    ext_gcd.push(make_tuple(max(m,n),min(m,n),-1,-1));
    while(get<1>(ext_gcd.top())!=0)
    {
        ext_gcd.push(make_tuple(get<1>(ext_gcd.top()),get<0>(ext_gcd.top())%get<1>(ext_gcd.top()),-1,-1));

    }
    ext_gcd.pop();
    float a,b;
    int x=0,y=1;
    while(!ext_gcd.empty())
    {
        b=get<1>(ext_gcd.top());
        a=get<0>(ext_gcd.top());
        int aux=x;
        x=y-floor(a/b)*x;
        y=aux;
        ext_gcd.pop();
    }
    return max(x,y);
}
vector<pair<int,int> >equations;
int CRT()//x=b (mod m), x=a (mod n)
{
    int sol;
    if(equations.size()==1)
    {
        sol=equations[0].first%equations[0].second;
    }
    else{
    int n1=equations[0].second,n2=equations[1].second;
    int a1=equations[0].first,a2=equations[1].first;
    int s=extn_gcd(n1,n2),lcm;
    int gc=gcd(n1,n2);
    if((a1-a2)%gc!=0)//gc=gcd(n1,n2)
    {
        cout<<"no solution\n";
        return 0;
    }
    else
    {
        lcm=n1*n2/gc;
        sol=(a1+s*(a2-a1)/gc%(n2/gc)*n1)%lcm;
        if(sol<0)sol+=lcm;
        sol%=lcm;
    }
    for(int j=2;j<equations.size();j++)
    {
        a1=sol%lcm;
        n1=lcm;
        a2=equations[j].first;
        n2=equations[j].second;
        s=extn_gcd(n1,n2);
        lcm=lcm*equations[j].second/gc;
        if((a1-a2)%gc!=0)
        {
            cout<<"no solution\n";
            continue;
        }
        else
        {
            int lcm=n1*n2/gc;
            sol=(a1+s*(a2-a1)/gc%(n2/gc)*n1)%lcm;
            if(sol<0)sol+=lcm;
            sol%=lcm;
        }
    }
    }
    return sol;
}
