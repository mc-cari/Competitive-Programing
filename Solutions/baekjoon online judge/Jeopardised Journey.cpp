#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e18
#define EPS 1e-8
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://www.acmicpc.net/problem/20910

struct point { ll x, y;   
    point() { x = y = 0.0; }                      
    point(ll _x, ll _y) : x(_x), y(_y) {}        
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }
    
    // by angles but with cross
    bool half() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const point &p) const
    {
        int h1 = half(), h2 = p.half();
        return h1 != h2 ? h1 > h2 : ((*this) ^ p) > 0;
    }

    db ang()
    {
        double a = atan2(y, x);
        while (a < 0) a += 2.0 * PI;
        return a;
    }

  };

db dist(const point& p1,const point& p2) {             
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
ll dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }

vl D, L, ap;
vector<vl> m;

ll rc = 0;
void dfs(int u, int p, int d)
{
    D[u] = L[u] = d;
    for (int v : m[u]) if (v != p)
    {
        if (D[v] == -1)
        {
            dfs(v, u, d + 1);
            if ((p == -1 && ++rc == 2) || (p != -1 && L[v] >= d)) ap[u] = 1;
            L[u] = min(L[u], L[v]); 
        }
        else if (D[v] < d) L[u] = min(L[u], D[v]);
    }
}

vl ans, vis;
void dfs2(int u)
{
    if(!vis[u]){
        vis[u] = 1;
        ans.push_back(u);
        if(!ap[u])
        for(int v : m[u])            
            dfs2(v);

    }
}

vector<point> G, H;
point pivot;
vl R;
struct Event
{
    db ang;
    ll d, tipe, i;

    bool operator<(const Event& b) const { 

        if(abs(ang - b.ang) > EPS)
            return ang < b.ang;
        if(tipe != b.tipe)
            return tipe < b.tipe;
        return d < b.d;

    }

};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll g, h;
    cin >> g >> h;
    point p;
    for(int i = 0; i < g; i++)
    {
        cin >> p.x >> p.y;
        G.push_back(p);
    }
    for(int i = 0; i < h; i++)
    {
        ll x;
        cin >> p.x >> p.y >> x;
        H.push_back(p);
        R.push_back(x);
    }
    Event e;
    m.assign(g, vl());
    ap.assign(g+1, 0);
    D.assign(g+1, -1);
    L.assign(g+1, -1);
    vis.assign(g+1, 0);

    for(int i = 0; i < g; i++)
    {
        
        vector<Event> q;
        pivot = G[i];
        for(int j = 0; j < g; j++)
        {
            p = G[j] - G[i];

            if(i != j)
            {
                e.tipe = 0;
                e.i = j;
                e.ang = p.ang();
                e.d = dist_sq(G[j], G[i]);
                q.push_back(e);
            }
        }
        multiset<ll> dis;
        for(int j = 0; j < h; j++)
        {
            
            p.x = H[j].x - G[i].x;
            p.y = H[j].y - G[i].y;

            e.d = dist_sq(H[j], G[i]) - R[j]*R[j];
            e.tipe = -1;
            e.i = j;
            db aux = p.ang() - asin(R[j] / sqrt(p.norm_sq()));
            while(aux < 0) aux += 2*PI;
            e.ang = aux;
            q.push_back(e);

            e.tipe = 1;
            e.i = j;
            db aux2 = p.ang() + asin(R[j] / sqrt(p.norm_sq()));
            while(aux2 >= 2*PI) aux2 -= 2*PI;
            e.ang = aux2;
            q.push_back(e);
            //cout<<i<<" "<<p.x<<" "<<p.y<<" "<<aux<<" "<<aux2<<" "<<"**\n";
            if(aux2 < aux - EPS)
                dis.insert(e.d);
        }
        sort(ALL(q));
        //cout<<"tipe i  size  ang\n";
        db prev = -1;
        for(auto it : q)
        {
            //cout<<i<<" "<<it.tipe<<" "<<it.i<<" "<<dis.size()<<" "<<it.ang<<"*\n";
            if(it.tipe == -1)
                dis.insert(it.d);
            else if(it.tipe == 0)
            {
                
                if((dis.empty() || it.d < *dis.begin()) && abs(prev - it.ang) > EPS)
                {
                    
                    m[i].push_back(it.i);
                    prev = it.ang;
                }
            }
            else
                dis.erase(dis.find(it.d));
        }
    }
    dfs(g-1, -1, 0);
    vis[g-1] = 1;
    for(auto it : m[g-1])
    {
        dfs2(it);
    }

    
    sort(ALL(ans));
    for(int i = 0; i < ans.size(); i++)
    {
        cout<<ans[i]+1;
        if(i < ans.size() - 1)cout << " ";

    }
    cout << "\n";


}
