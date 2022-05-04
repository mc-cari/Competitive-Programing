#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
using namespace std;
typedef vector<ll> vl;
typedef long long ll;

int joseph(int n,int m)
{
    int Result=0;
    for(int i=1;i<=n;i++)
    {
        Result=(Result+m-1)%i+1;
    }
    return(Result);
}
int joseph(int n,int m)
{
    vl a(n+1, 0);
    //see eliminated
    bool o = 1;
    for(int i = 0; i < n/2; i++)
    {
        
        a[i+1] = (a[i] + m-1)%(n-i);
        if(a[i+1] < n/2 )
        {
            o = 0;
            break;
        }
        
    }
}
// if k = 2
// move first significant bit to right
int joseph(ll n)
{
    ll bit = 62;
    while(!(n & (1 << bit)))
    {
        bit--;
    }
    n &= ~(1 << bit);
    return 1 + (n << 1);
}


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
