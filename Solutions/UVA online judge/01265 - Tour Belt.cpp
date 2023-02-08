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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3706

struct UF{
    vl p, r, tam;
    UF(ll n)//cambiar cuando no es int
    {
        for(ll i = 0; i < n; i++)
        {
            p.push_back(i);
            r.push_back(0);
            tam.push_back(1);
        }
    }
    ll find(ll x)
        {return p[x] = p[x] == x ? x : find(p[x]);}
    void join(ll x, ll y)
    {
        x = find(x);
        y = find(y);
        ll sum = tam[x] + tam[y];
        if(x != y)
        {

            if(r[x] >= r[y])
            {
                if(r[x] == r[y]) r[x]++;
                p[y] = x;
                tam[x] = sum;
            }
            else 
            {
                p[x] = y;
                tam[y] = sum;
            }

        }


    }
};

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while(t--)
    {
        ll n, m, x, y, v, a, b;
        cin >> n >> m;
        vector<tuple<ll, ll, ll>> d;
        ll mini[n][n], maxi[n][n];
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) 
        {
            mini[i][j] = INF;
            maxi[i][j] = 0;
        }
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y >> v;
            d.push_back({v, x-1, y-1});
            mini[x-1][y-1] = mini[y-1][x-1] = v;
            maxi[x-1][y-1] = maxi[y-1][x-1] = v;
            
        }

        sort(ALLR(d));
        UF uf(n);
        ll ans = 0;
        for(auto it : d)
        {
            tie(v, x, y) = it;
            a = uf.find(x); b = uf.find(y);
            if(a != b)
            {
                
                uf.join(x, y); 
                ll s = uf.find(x); 

                ll out = 0, in = INF;

                for(int j = 0; j < n; j++)
                {
                    ll rep = uf.find(j);
                    mini[s][j] = mini[j][s] = min(min(mini[x][j], mini[y][j]), mini[s][j]);
                    maxi[s][j] = maxi[j][s] = max(max(maxi[x][j], maxi[y][j]), maxi[s][j]);
                    if(uf.find(j) != s) out = max(out, maxi[s][j]);
                    else in = min(in, mini[s][j]);
                }
                if(out < in) ans += uf.tam[s];
            }
        }
        cout << ans << "\n";

    }
    

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
