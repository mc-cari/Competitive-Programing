#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

struct point { db x, y;     
    db norm_sq() const{ return x*x + y*y; }
    db ang()
    {
        db a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };
vector<point> Q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n;
    db x, y;
    cin >> n;
    
    Q.resize(n);
    for(int i = 0; i < n; i++)
    {
        cin >> x >> y;
        //while(!(p.x >= 0 && p.y >= 0) || (p.y > 0 && p.x == 0.0))p = p.rot();
        Q[i] = {x, y};
    }
    db l = 0 ,r = 1e10;
    for(int j = 0; j < 65; j++)
    {
        db d = (l + r) / 2.0;
        bool o = 0;
        int cont = 0, tot = 0;
        set<pair<db, int> > sweep;
        for(int i = 0; i < n; i++)
        {
            if(Q[i].norm_sq() >= d*d*2) continue;
            
            if(Q[i].norm_sq() < d*d ) goto skip;
            db ang = acos(d / sqrt(Q[i].norm_sq()));
            db an = Q[i].ang();
            db a1 = an - ang, a2 = an + ang;
            
            if(a1 < 0) a1 += 2*PI;
            while (a1 >= 0.5 * PI)
                a1 -= 0.5 * PI;
            while (a2 >= 0.5 * PI)
                a2 -= 0.5 * PI;
            sweep.insert({a1, -1});
            sweep.insert({a2, 1});
            tot++;
            if(a1 > a2) cont++;
        }
        for(auto it : sweep)
        {
            cont += -it.second;
            if(cont == tot){
                 o = 1;
                 break;
            }
            
        }
        if(tot == cont) o = 1;
        
        skip:
        if(o)
        {
            l = d;
        }
        else r = d;
    }
    cout << setprecision(4) << fixed;
    cout << l * 8.0 << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
