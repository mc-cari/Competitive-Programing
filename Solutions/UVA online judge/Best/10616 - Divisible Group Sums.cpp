#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1557
ll V[10000],W[10000],memo[210][30][20];
ll N,Q,x,D,M;
vl c;

// Top Down
ll DP(ll i, ll v, ll cont)
{
    if(cont==M)
    {
        if(v==0)return 1;
        return 0;
    }
    if(memo[i][v][cont]!=-1)return memo[i][v][cont];
    ll sum=0;

    if(M-cont<i+1)
    {
        sum+=DP(i-1,v,cont);
    }
    ll aux=(v+c[i])%D;
    if(aux<0)aux+=D;
    sum+=DP(i-1,(aux)%D,cont+1);
    return memo[i][v][cont]=sum;

}

int main()
{
    ll t=1;
    while(cin>>N>>Q&&(N+Q))
    {
        c.clear();
        for(ll i=0;i<N;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        cout<<"SET "<<t<<":\n";
        t++;
        ll q=1;
        while(Q--)
        {
            memset(memo,-1,sizeof(memo));
            cin>>D>>M;
            cout<<"QUERY "<<q<<": ";
            cout<<DP(N-1,0,0)<<"\n";
            q++;
        }
    }

    return 0;
}
