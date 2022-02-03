 #include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://codeforces.com/contest/1316/problem/E
vector<pll> c;
vector<vl>d;
ll p,k,n;
ll memo[100002][200];

ll DP(ll in,unsigned int bit,ll cont)
{

    if(in<0)return 0;

    if(memo[in][bit]!=-1)return memo[in][bit];
    int t=c[in].second;
    ll maxi=0;
    unsigned int mul=1;
    for(int i=0;i<p;i++)
    {
        if(!(bit & (mul)))
        {
            maxi=max(maxi,DP(in-1,bit|mul,cont)+d[t][i]);
        }
        mul=mul<<1;
    }
    if(cont<k)
    {
        maxi=max(maxi,DP(in-1,bit,cont+1)+c[in].first);
    }
    else maxi=max(maxi,DP(in-1,bit,cont));
    return memo[in][bit]=maxi;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll x;
    cin>>n>>p>>k;
    memset(memo,-1,sizeof(memo));
    d.assign(n,vl(0));
    for(int i=0;i<n;i++)
    {
        cin>>x;
        c.push_back(make_pair(x,i));
    }
    sort(ALL(c));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p;j++)
        {
            cin>>x;
            d[i].push_back(x);
        }
    }
    cout<<DP(n-1,0,0)<<"\n";
    return 0;
}
