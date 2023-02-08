 #include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://acm.timus.ru/problem.aspx?space=1&num=1185
// ----------------------------------------------
// Convex Hull: Andrew's Montone Chain Algorithm
// ----------------------------------------------
//https://github.com/PabloMessina/Competitive-Programming-Material/blob/master/Geometry/ConvexHull.cpp
struct Point {
    ll x, y;
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
double dist(Point a, Point b)
{
    return sqrt((double)(a.x - b.x) * (double)(a.x - b.x) +(double)(a.y - b.y) * (double)(a.y - b.y));
}
ll cross(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}

vector<Point> upper_hull(vector<Point>& P) {
    // sort points lexicographically
    int n = P.size(), k = 0;
    sort(P.begin(), P.end());
    // build upper hull
    vector<Point> uh(n);
    for(int i = n-1; i >= 0; --i){
        while (k >= 2 && cross(uh[k-2], uh[k-1], P[i]) <= 0) k--;
        uh[k++] = P[i];
    }
    uh.resize(k);
    return uh;
}

vector<Point> lower_hull(vector<Point>& P) {
    // sort points lexicographically
    int n = P.size(), k = 0;
    sort(P.begin(), P.end());
    // collect lower hull
    vector<Point> lh(n);
    for(int i=0;i<n;i++) {
        while (k >= 2 && cross(lh[k-2], lh[k-1], P[i]) <= 0) k--;
        lh[k++] = P[i];
    }
    lh.resize(k);
    return lh;
}

vector<Point> convex_hull(vector<Point>& P) {
    int n = P.size(), k = 0;
    // set initial capacity
    vector<Point> H(2*n);
    // sort points lexicographically
    sort(P.begin(), P.end());
    // build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    // build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    // remove extra space
    H.resize(k-1);
    return H;
}

int main()
{
    double n,l,x,y;
    vector<Point>c;
    Point a;
    cin>>n>>l;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        a.x=x;
        a.y=y;
        c.push_back(a);
    }

    vector<Point> d=convex_hull(c);
    d.push_back(d[0]);
    double ans=0;
    for(int i=1;i<d.size();i++)ans+=dist(d[i],d[i-1]);
    ans+=2*pi*l;
    cout<<round(ans)<<"\n";
    return 0;
}
