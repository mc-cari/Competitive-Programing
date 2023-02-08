#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2169

struct UF{
    vector<int>p,r;
    int conjuntos=0;
    UF(int n)//cambiar cuando no es int
    {
        conjuntos = n;
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
        conjuntos--;
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

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t, cas = 1;
    cin >> t;
    while(t--)
    {
        ll n, r, x, y;
        cin >> n >> r;
        priority_queue<tuple<ll, ll, ll> ,vector<tuple<ll, ll, ll> >,greater<tuple<ll, ll, ll> > >q;
        vp c;
        for(int i = 0; i < n; i++)
        {
            cin >> x >> y;
            c.push_back({x, y});
        }
        for(int i = 0; i < n; i++)for(int j = i+1; j < n; j++)
        {
            q.push(make_tuple((c[i].first-c[j].first)*(c[i].first-c[j].first) + (c[i].second-c[j].second)*(c[i].second-c[j].second), i, j));
        }
        UF u(n);
        ll states = -1;
        db ans = 0, ans2 = 0;
        while(!q.empty())
        {
            ll dist;
            tie(dist, x, y) = q.top();
            q.pop();
            if(states == -1 && r*r < dist) states = u.conjuntos;
            if(u.find(x) != u.find(y))
            {
                u.join(x, y);
                if(states == -1)
                ans += sqrt(dist);
                else ans2 += sqrt(dist);
            }
            
        }
        if(states == -1)states = 1;
        cout<<"Case #"<<cas<<": "<<states<<" "<<round(ans)<<" "<<round(ans2)<<"\n";
        cas++;
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
