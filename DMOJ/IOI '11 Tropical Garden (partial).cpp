#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://dmoj.ca/problem/ioi11p1
//Partial score (TLE)

ll maxlog2(ll x){
    return (63 - __builtin_clzll(x));
}
struct SparseTable
{
    vector<vl >SP;
    SparseTable(vl& nex, ll n)
    {

        SP.clear();
        SP.push_back(nex);
        ll maxlg=maxlog2(1000000000);
        for(ll i = 1 ; i <= maxlg; i++)
        {
            vl c;
            for(ll j = 0 ; j < n; j++)
            {
                if(SP[i-1][j] != -1)
                c.push_back(SP[i-1][SP[i-1][j]]);
                else c.push_back(-1);
            }
            SP.push_back(c);
        }
        
    }
    ll op(ll k, ll pos)
    {

        while(k)
        {
            ll maxlg = maxlog2(k);

            pos = SP[maxlg][pos];
            k -= (1LL << maxlg);
            
        }
        return pos;
    }
};

void count_routes(int n, int m, int p, int R[][2], int q, int G[])
{

    

    vector<vp> g(n, vp());
    for(int i = 0; i < m; i++) {
        ll a = R[i][0], b = R[i][1];
        
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    vp dest;
    vl nex(2 * n, -1);
    for(int i = 0; i < n; i++)
    {
        ll mini = INF, dest1 = -1, mini2 = INF, dest2 = -1;
        for(auto it : g[i])
        {
            if(mini > it.second)
            {
                mini2 = mini;
                dest2 = dest1;
                mini = it.second;
                dest1 = it.first;
            }
            else if(mini2 > it.second)
            {
                mini2 = it.second;
                dest2 = it.first;
            }
        }
        if(mini2 == INF) dest2 = dest1;
        dest.push_back({dest1, dest2});
        
    }
    
    for(int i = 0; i < n; i++)
    {
        ll u = dest[i].first;
        if(dest[u].first == i) nex[i] = u + n;
        else nex[i] = u;

        u = dest[i].second;
        if(dest[u].first == i) nex[i + n] = u + n;
        else nex[i + n] = u;
    }

    SparseTable SP(nex, 2 * n);

    for(int j = 0; j < q; j++)
    {
        ll k = G[j], ans = 0;
        
        for(int i = 0; i < n; i++)
        {
            ll pos = SP.op(k, i);
            if(pos >= n) pos -= n;
            if(pos == p) ans++;
        }
        answer(ans);

    }

}
int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    


    return 0;
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
