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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1398

struct UF{
    vl p, r;
    UF(ll n)//cambiar cuando no es int
    {
        for(ll i = 0; i < n; i++)
        {
            p.push_back(i);
            r.push_back(0);
        }
    }
    ll find(ll x)
        {return p[x] = p[x] == x ? x : find(p[x]);}
    void join(ll x, ll y)
    {
        x = find(x);
        y = find(y);
        if(x != y)
        {

            if(r[x] >= r[y])
            {
                if(r[x] == r[y]) r[x]++;
                p[y] = x;
            }
            else p[x] = y;
        }
    }
};

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    

    ll n, m, x, y, v, a, b;
    while(cin >> n >> m)
    {
        vector<tuple<ll,ll,ll>> d;
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y >> v;
            d.push_back({v, x-1, y-1});
        }

        sort(ALL(d));
        

        
        cin >> a >> b;
        ll q;
        cin >> q;
        while(q--)
        {
            ll s, t;
            cin >> s >> t;
            ll mini = INF;
            s--; t--;
            // for every edge, set it as the minimum cost, an then calculate the minimun max cost edge that from edges [i, m], s and t are connected
            // Look for the minimum gap between min and max edge
            // optimization: only use  edges from the start as the minimum edge
            for(int i = 0; i < m; i++)
            {
                UF uf(n);
                for(int j = i; j < m; j++)
                {
                    tie(v, y, x) = d[j];
                    if(uf.find(x) != uf.find(y))
                    {
                        
                        uf.join(x, y);  
                        if(uf.find(s) == uf.find(t))
                        {
                            mini = min(mini, v - get<0>(d[i]));
                            break;
                        }
                    }
                }
            }
            cout << mini + a + b << "\n";
        }
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
