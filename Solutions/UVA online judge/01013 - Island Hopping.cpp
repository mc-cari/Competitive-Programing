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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3454

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

    ll n, T = 0;
    while(cin >> n && n)
    {
        T++;
        ll m, x, y, v;
        vector<db> siz;
        vector<tuple<db,ll,ll>> d;
        vp c;
        for(int i = 0; i < n; i++)
        {
            cin >> x >> y >> v;
            c.push_back({y, x});
            siz.push_back(v);
        }
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                db a1 = c[i].first - c[j].first;
                db a2 = c[i].second - c[j].second;
                d.push_back(make_tuple(sqrt(a1*a1 + a2*a2), i, j));
            }
        }
        sort(ALL(d));
        UF uf(n);
        db up = 0, down = 0;
        down += siz[0];
        for(auto it : d)
        {
            db k;
            tie(k, y, x) = it;
            if(uf.find(x) != uf.find(y))
            {
                if(uf.find(x) == uf.find(0) && uf.find(y) != uf.find(0))
                {
                    for(int i = 0; i < n; i++)
                    {
                        if(uf.find(i) == uf.find(y))
                        {
                            up += siz[i] * k;
                            down += siz[i];
                        }
                    }
                }
                else if(uf.find(x) != uf.find(0) && uf.find(y) == uf.find(0))
                {
                    for(int i = 0; i < n; i++)
                    {
                        if(uf.find(i) == uf.find(x))
                        {
                            up += siz[i] * k;
                            down += siz[i];
                        }
                    }
                }
                uf.join(x, y);
               
                
            }
        }
        cout << setprecision(2) << fixed << "Island Group: " << T << " Average " << up/down << "\n\n";
        
    }
    char d;
    cin >> d;
    


    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
