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

//https://open.kattis.com/problems/mravi

vl s, v;
void dfs(int t, vector<vector<tuple<ll, ll, ll>>> &g)
{
    v[t] = 1;
    for(auto it : g[t]){

        if(!v[get<0>(it)])
            dfs(get<0>(it), g);
    }
    s.push_back(t);
}
int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vl K;

    vector<vector<tuple<ll, ll, ll>>> g(n, vector<tuple<ll, ll, ll>>());

    for(int i = 0; i < n-1; i++)
    {
        ll a, b, x, t;
        cin >> a >> b >> x >> t;
        a--; b--;
        g[b].push_back({a, x, t});
    }
    vector<db> d(n, -1);
    for(int i = 0; i < n; i++)
    {
        ll k;
        cin >> k;
        if(k != -1)
            d[i] = k;
        K.push_back(k);
    }
    
    v.assign(n, 0);

    for(int i = 0; i < n; i++)
        if(!v[i])
            dfs(i, g);

    reverse(ALL(s));

    for(auto node : s)
    {
        
        if(d[node] == -1)continue;
        for(auto it : g[node])
        {
            db b, t;
            db x, aux = d[node];
            tie(b, x, t) = it;
            if(t == 1) aux = sqrt(aux);
            aux *= 100;
            aux /= x;
            d[b] = max(d[b], aux);   
        }
        
    }
    cout << fixed << setprecision(4) << d[0] << "\n";

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}