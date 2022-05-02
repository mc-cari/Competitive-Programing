#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://matcomgrader.com/problem/9643/improve-spam/

ll M = 1e9 + 7;

set<ll> v;
ll memo[100000];
ll dp(ll in, vector<vl>& g)
{
    if(memo[in] != -1)return memo[in];

    ll res = 0;
    for(auto it : g[in])
    {
        res += dp(it, g);
        res %= M;
    }
    if(g[in].size() == 0) 
    {
        v.insert(in);
        res++;
    }
    return memo[in] = res % M;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, l, x;
    cin >> n >> l;
    memset(memo, -1, sizeof(memo));
    vector< vl > g(n, vl(0));
    for(int i = 0; i < l; i++)
    {
        ll k;
        cin >> k;
        for(int j = 0; j < k; j++)
        {
            cin >> x;
            g[i].push_back(x - 1);
        }
    }
    dp(0, g);
    cout << dp(0, g) << " " << v.size() << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
