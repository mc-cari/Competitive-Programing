#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef ll db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.urionlinejudge.com.br/judge/es/problems/view/1468

struct point { db x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(db _x, db _y) : x(_x), y(_y) {}        // user-defined
    bool operator <(const point& other) const
    {
        return (x < other.x ? true : (x == other.x && y < other.y));
    }

    bool operator == (const point& other) const
    {
        return abs(other.x - x) < EPS && abs(other.y - y) < EPS;
    }

    point operator + (const point& other) const
    {
        return point(this->x + other.x, this->y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }
    point operator * (long double other) const
    {
        return point(this->x * other, this->y * other);
    }

    point operator / (long double other) const
    {
        return point(this->x / other, this->y / other);
    }

  };
vector<pair<point, point> > segs;

struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

vec scale(vec v, db s) {        // nonnegative s = [<1 .. 1 .. >1]
  return vec(v.x*s, v.y*s); }                   // shorter.same.longer


db cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0; }

struct cmp{
    bool operator()(int x, int y){
        if(segs[x].first.x <= segs[y].first.x)
            return ccw(segs[x].first, segs[x].second, segs[y].first);
        else
            return !ccw(segs[y].first, segs[y].second, segs[x].first);   
    }
};
vp memo;
pll dp(ll in, vl& parent, ll x)
{
    if(memo[in].first != -1)return memo[in];

    if(segs[in].first.y == segs[in].second.y)
    {
        return {x, segs[in].first.y};
    }
    else
    {
        ll aux = segs[in].first.x;
        if(segs[in].second.y > segs[in].first.y) aux = segs[in].second.x;
        if(parent[in] == -1)
        {
            return memo[in] = {aux, -1};
        }
        else
            return memo[in] = dp(parent[in], parent, aux);
    }
    
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, c, x1, x2, y1, y2;
    while(cin >> n >> c){
        segs.clear();
        memo.assign(100005, pll(-1, -1));

        vector<tuple<ll, ll, ll, ll> >q;
        for(int i = 0; i < n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            if(x1 > x2)
            {
                swap(x1, x2);
                swap(y1, y2);
            }
            q.push_back({make_tuple(x1, 0, y1, i)});
            q.push_back({make_tuple(x2, 2, y2, i)});
            segs.push_back({point(x1, y1), point(x2, y2)});

        }
        vl ballons;
        for(int i = 0; i < c; i++)
        {
            cin >> x1;
            ballons.push_back(x1);
            q.push_back({make_tuple(x1, 1, -1, i)});
        }
        
        set<ll, cmp > ord;
        sort(ALL(q));
        vl parent(n, -1), bs(c, -1);
        for(auto it : q)
        {
            ll id, tipe;
            
            tie(x1, tipe, y1, id) = it;
            if(tipe == 0)
            {
                auto it2 = ord.insert(id);
                if(segs[id].first.y > segs[id].second.y && next(it2.first) != ord.end())
                    parent[id] = *next(it2.first);
                
            }
            else if(tipe == 2)
            {
                auto it2 = ord.find(id);
                auto auxit = next(it2);
                if(segs[id].first.y < segs[id].second.y && auxit != ord.end())
                    parent[id] = *auxit;
                ord.erase(it2);
            }
            else
            {
                if(!ord.empty())
                    bs[id] = *ord.begin();
            }
        }

        for(int i = 0; i < c; i++)
        {
            if(bs[i] == -1)cout << ballons[i] << "\n";
            else
            {
                pll res = dp(bs[i], parent, ballons[i]);
                if(res.second == -1)
                    cout << res.first << "\n";
                else cout << res.first << " " << res.second << "\n";
            }
            
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
