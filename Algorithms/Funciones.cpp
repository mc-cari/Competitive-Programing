#include<bits/stdc++.h>
using namespace std;

using namespace chrono;
auto start1 = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start1);
//cerr << duration.count()/1000 << "ms" << endl;

vector <bool> crib;
void criba(ll b)
{
    crib.assign(b, 1);
    crib[0] = 0;
    crib[1] = 0;
    for(int k=2; k < sqrt(b + 1) + 1; k++)
    {
        if(crib[k])
        {
            for(int j=2; (j * k) < b + 1; j++)//para optimizar j=k
            {
                crib[k*j] = 0;
            }
        }
    }
}

vector<ll> factorial_decomp(ll n)
{
    vl sol(primos.size(),0);
    ll in = 0;
    while(in != primos.size() && primos[in] <= n)
    {
        ll tmp = 1;
        for(ll k=1; k<=(log(n) / log(primos[in])) + 1; k++)
        {
            tmp *= primos[in];
            sol[in] += n / pow(primos[in], k);
        }
        in++;
    }
    return sol;
}

// stores smallest prime factor for every number
int spf[MAXN];
 
// Calculating SPF (Smallest Prime Factor) for every
// number till MAXN.
// Time Complexity : O(nloglogn)
void sieve()
{
    spf[1] = 1;
    for (int i=2; i<MAXN; i++)
 
        // marking smallest prime factor for every
        // number to be itself.
        spf[i] = i;
 
    // separately marking spf for every even
    // number as 2
    for (int i=4; i<MAXN; i+=2)
        spf[i] = 2;
 
    for (int i=3; i*i<MAXN; i++)
    {
        // checking if i is prime
        if (spf[i] == i)
        {
            // marking SPF for all numbers divisible by i
            for (int j=i*i; j<MAXN; j+=i)
 
                // marking spf[j] if it is not
                // previously marked
                if (spf[j]==j)
                    spf[j] = i;
        }
    }
}
 
// A O(log n) function returning primefactorization
// by dividing by smallest prime factor at every step
vector<int> getFactorization(int x)
{
    vector<int> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}

void primeFactors(ll n)  
{    
    while (n % 2 == 0)  
    {  
        cout << 2 << " ";  
        n = n/2;  
    }  
  
    for (int i = 3; i <= sqrt(n); i = i + 2)  
    {   
        while (n % i == 0)  
        {  
            cout << i << " ";  
            n = n/i;  
        }  
    }  
  
    if (n > 2)  
        cout << n << " ";  
}

//archivos
ifstream input;
input.open("divisibility-tree.in");
input >> n;
ofstream output;
output.open("divisibility-tree.out");
output<<" ";  
output.close();

// suma subconjuntos
for i = 0 to n-1
for mask = 0 to (1«n) - 1
if (mask & (1«i))
dp(mask) += dp(mask - (1«i))

// suma divisores
for p ∈ P
for x ∈ S (DE MENOR A MAYOR)
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
int maxlog2(int x) //potecncia de 2 mayor que es menor o igual a x
{
    // ll maxlog = 63 - __builtin_clzll(x);
    int maxlog = 31 - __builtin_clz(x);
    return maxlog;
}
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
int res(int a,int b)
{
    int c=1,d;
    for(int i=0;i<b;i++)
    {
        c*=10;
    }
    d=c*10;
    a=a-(a-a%d);
    a=a-(a%c);
    a=a/c;
    return a;
}
int gcd(int a,int b)//max a
{
    if (b==0)return a;
    return gcd(b,a%b);
}
int extn_gcd(int m,int n)// retorna inverso modular b*b-1=1(mod n)
{
    stack<tuple<int,int,int,int> >ext_gcd;
    ext_gcd.push(make_tuple(max(m,n),min(m,n),-1,-1));
    while(get<1>(ext_gcd.top())!=0)
    {
        ext_gcd.push(make_tuple(get<1>(ext_gcd.top()),get<0>(ext_gcd.top())%get<1>(ext_gcd.top()),-1,-1));
        //cout<<get<0>(ext_gcd.top())<<" "<<get<1>(ext_gcd.top())<<endl;
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

//propagate val in mask to all its submask
for (int i = 0; i < p; i++)
{
    for(int s = 0; s < (1 << p); s++)
    {
        if((s & (1 << i)) == 0)
            f[s] += f[s | (1 << i)];
    }
}

int bit_opst(ll N,ll S)
{
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

//Euler Tour
vl L, R, d, c;
ll num = -1;
vector<vl>g;
void dfs(ll in, ll p)
{
    num++;
    L[in] = num;
    d.push_back(c[in]);
    for(auto it : g[in])
    {
        if(p != it)
            dfs(it, in);
    } 
    R[in] = num;
}
int main()
{

    return 0;
}
