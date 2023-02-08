#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/contest/1025/problem/F

struct point { db x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(db _x, db _y) : x(_x), y(_y) {}
    bool operator < (point other) const { 
    if (fabs(y-other.y) > EPS)                   
      return y < other.y;          
    return x < other.x; }         

    bool operator == (point other) const {
      return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
    point operator - (point other) const{
        point aux(x-other.x,y-other.y);
        return aux;
    }
    point operator + (point other) const{
        point aux(x+other.x,y+other.y);
        return aux;
    }
    point operator * (db other) const{
        point aux(x*other,y*other);
        return aux;
    }
    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }
  };      // constructor

db dist(point& p1, point& p2) {                // Euclidean distance
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }

struct vec { db x, y;  // name: `vec' is different from STL vector
  vec(db _x, db _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x - a.x, b.y - a.y); }

// returns the cross product of two vectors a and b
ll cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }



vector<point> Q, ord;
bool cmp(pll& a, pll& b)
{
    
    vec A = toVec(Q[a.first], Q[a.second]);
    vec B = toVec(Q[b.first], Q[b.second]);

    if(fabs(cross(A, B)) < EPS)return 0;
    return cross(A, B) >= 0;
    
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    db x, y;
    
    vl in(n, 0);
    for(int i = 0; i < n; i++)
    {

        cin >> x >> y;
        point p(x, y);
        Q.push_back(p);

    }
    sort(ALL(Q));
    for(int i = 0; i < n; i++)
    {
        in[i] = i;
        ord.push_back(Q[i]);
    }

    vector<pll > rec;
    for(int i = 0; i < n; i++)for(int j = i+1; j < n; j++)
    {
        rec.push_back({i, j});
    }

    
    sort(ALL(rec), cmp);

    ll ans = 0;
    for(int i = 0; i < rec.size(); i++)
    {
        
        db angg, a, b;
        point aux;
        a = rec[i].first;
        b = rec[i].second;

        ans += (in[a] - 1) * in[a] / 2 * (n - in[b] - 2) * (n - in[b] - 1) / 2;

        swap(ord[in[a]], ord[in[b]]); swap(in[a], in[b]);

    }

    cout<< ans << "\n";
}
