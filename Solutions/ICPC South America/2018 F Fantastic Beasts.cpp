#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
 //https://www.beecrowd.com.br/judge/es/problems/view/2908
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 6e18
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)



inline ll mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }
inline ll mul(ll x, ll y, ll m) { return (x * y) % m; }
inline ll add(ll x, ll y, ll m) { return (x + y) % m; }

// extended euclidean algorithm
// finds g, x, y such that
//    a * x + b * y = g = GCD(a,b)
ll gcdext(ll a, ll b, ll& x, ll& y) {
    ll r2, x2, y2, r1, x1, y1, r0, x0, y0, q;
    r2 = a, x2 = 1, y2 = 0;
    r1 = b, x1 = 0, y1 = 1;
    while (r1) {
        q = r2 / r1;
        r0 = r2 % r1;
        x0 = x2 - q * x1;
        y0 = y2 - q * y1;
        r2 = r1, x2 = x1, y2 = y1;
        r1 = r0, x1 = x0, y1 = y0;        
    }
    ll g = r2; x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y; // make sure g > 0
    // for debugging (in case you think you might have bugs)
    // assert (g == a * x + b * y);
    // assert (g == __gcd(abs(a),abs(b)));
    return g;
}

#define rep(i,a,b) for (int i=a; i<b; ++i)
pair<ll,ll> CRT(vl& r, vl& m, int n) {
    ll r1 = r[0], m1 = m[0];
    rep(i,1,n) {
        ll r2 = r[i], m2 = m[i];
        ll g, x, y; g = gcdext(m1, m2, x, y);
        if ((r1 - r2) % g != 0) return {-1, -1}; // no solution
        ll z = m2/g;
        ll lcm = m1 * z;
        ll sol = add(mod(r1, lcm), m1*mul(mod(x,z),mod((r2-r1)/g,z),z), lcm);
        r1 = sol;
        m1 = lcm;
    }
    // for debugging (in case you think you might have bugs)
    // assert (0 <= r1 and r1 < m1);
    // rep(i,0,n-1) assert (r1 % m[i] == r[i]);
    return {r1, m1};
}
ll B, Z;

vl pos, incicle;
vector<vl>mov, his, vis, cicle;
ll cont = 0, ans, T = 0;

bool simulate()
{
    T++;
    set<ll> check;
    for(int i = 0; i < B; i++)
    {
        pos[i] = mov[i][pos[i]];
        check.insert(pos[i]);
        his[i].push_back(pos[i]);
        if(vis[i][pos[i]])
        {
            if(incicle[i] == 0)cont ++;
            incicle[i] = 1;
            
        }
        vis[i][pos[i]] = 1;
    }
    if(check.size() == 1)
    {
        ans = (*check.begin()) + 1;
        return 1;
    }
    return 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> B >> Z;

    mov.assign(B, vl());
    his.assign(B, vl());
    vis.assign(B, vl(Z, 0));
    incicle.assign(B, 0);
    cicle.assign(B, vl());
    set<ll> check;
    for(int i = 0; i < B; i++)
    {
        for(int j = 0; j < Z+1; j++)
        {
            int x;
            cin >> x;
            x--;
            if(j == 0) 
            {
                check.insert(x);
                pos.push_back(x);
                his[i].push_back(x);
                vis[i][x] = 1;
            }
            else
            {
                mov[i].push_back(x);
            }
        }
    }
    if(check.size() == 1)
    {
        cout << *(check.begin()) + 1 << " " << 0 << "\n";
        return 0;
    }
    bool o = 0;
    while(cont < B)
    {
        if(simulate()) 
        {
            o = 1;
            break;
        }
    }
    if(o)
    {
        cout << ans << " " << T << "\n";
        return 0;
    }

    

    for(int i = 0; i < B; i++){
        ll pivot = pos[i];
        cicle[i].push_back(pivot);
        his[i].pop_back();
        while(his[i].back() != pivot)
        {
            cicle[i].push_back(his[i].back());
            his[i].pop_back();
        }
        reverse(ALL(cicle[i]));

    }
    ans = INF;
    ll mini = INF;
    for(int i = 0; i < Z; i++)
    {
        vl r, m;
        for(int j = 0; j < B; j++)
        {
            ll in = -1;
            for(int z = 0; z < cicle[j].size(); z++)
            {
           
                if(cicle[j][z] == i)
                {
                    in = z;
                    break;
                }
            }
           
            if(in == -1)break;

            r.push_back(in);
            m.push_back(cicle[j].size());

        }
        
        if(r.size() == B)
        {
            //cout<<i<<":\n";
            pll sol = CRT(r, m, B);
            if(sol.first != -1)
            {
                if(mini > sol.first)
                {
                    mini = sol.first;
                    ans = i + 1;
                }
                
            }
            
        }
    }
    
    if (mini == INF) cout << "*\n";
    else cout << ans << " " << mini + T + 1<< "\n";
   

    

    
    
    
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
