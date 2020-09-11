#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://www.spoj.com/problems/MST/en/

struct UF{
    vector<int>p,r;
    int conjuntos=0;
    UF(int n)//cambiar cuando no es int
    {
        for(int i=0;i<n;i++)
        {
            p.push_back(i);
            r.push_back(0);
        }
    }
    int find(int x)
    {
        return p[x] = p[x] == x ? x : find(p[x]);
    }
    void join(int x,int y)
    {
        x=find(x);
        y=find(y);
        if(x!=y)
        {
            if(r[x]>=r[y])
            {
                if(r[x]==r[y]) r[x]++;
                p[y]=x;
            }
            else p[x]=y;
        }
    }
};

ll M = 1000000007;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, m, x, y, k;
    cin >> n >> m;
    vector<vl> g(n, vl(0));
    priority_queue<tuple<ll, ll, ll> ,vector<tuple<ll, ll, ll> >,greater<tuple<ll, ll, ll> > >q;
    for(int i = 0; i < m; i++)
    {
        cin >> x >> y >> k;
        x--; y--;
        q.push(make_tuple(k, x, y));
    }
    UF u(n);
    ll ans = 0;
    while(!q.empty())
    {
        tie(k, x, y) = q.top();
        q.pop();
        if(u.find(x) != u.find(y))
        {
            ans += k;
            u.join(x, y);
        }
    }
    cout<<ans<<"\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
