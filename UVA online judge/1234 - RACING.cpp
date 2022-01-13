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

    ll t;
    cin >> t;
    while(t--)
    {
        ll n, m, x, y, v;
        cin >> n >> m;
        vector<tuple<ll,ll,ll>> c;
        ll sum = 0;
        for(int i = 0; i < m; i++)
        {
            cin >> x >> y >> v;
            c.push_back(make_tuple(v, y, x));
            sum += v;
        }
        sort(ALLR(c));
        UF uf(n);
        for(auto it : c)
        {
            tie(v, y, x) = it;
            if(uf.find(x-1) != uf.find(y-1))
            {
                uf.join(x-1, y-1);
                sum -= v;
                
            }
        }
        cout << sum << "\n";
    }
    char d;
    cin >> d;
    


    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
