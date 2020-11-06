#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/TAP2016D/

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
    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }
    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }
  };


db dist(point& p1, point& p2) {                // Euclidean distance
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }
db angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }
// angle from 0 to 2*PI

db cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }


ll grid[230][230];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    db n, x, y;
    while(cin >> n){

        vector<point>Q;
        for(int i = 0; i < 225; i++)for (int j = 0; j < 225; j++)
            grid[i][j] = 0;


        point p, a1, a2, a3;
        cin >> a1.x >> a1.y >> a2.x >> a2.y >> a3.x >> a3.y;
        grid[ll(a1.x) + 100][ll(a1.y) + 100] = 1;
        grid[ll(a2.x) + 100][ll(a2.y) + 100] = 1;
        grid[ll(a3.x) + 100][ll(a3.y) + 100] = 1;
        db ab = dist(a1, a2), bc = dist(a2, a3), ca = dist(a3, a1);
        db ang1 = angle(a3, a1, a2), ang2 = angle(a1, a2, a3);


        for(int i = 0; i < n - 3; i++)
        {
            cin >> p.x >> p.y;
            grid[ll(p.x) + 100][ll(p.y) + 100] = 1;
            Q.push_back(p);
        }
        Q.push_back(a1);
        Q.push_back(a2);
        Q.push_back(a3);

        ll mult = 1;
        if(ab == bc && bc == ca)mult = 3;
        else if(ab == bc || bc == ca || ca == ab)mult = 2;

        ll ans = 0;

        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                if(i == j) continue;
                point aux2;
                aux2.x = Q[i].x + 10;
                aux2.y = Q[i].y;
                db pond = dist(Q[i], Q[j]) / ab, base = (Q[j] - Q[i]).ang();
                point aux;
                db ang = base + ang1;
                if(ang >= 2 * PI) ang -= 2* PI;
                aux.x = ca * pond * cos(ang) + Q[i].x;
                aux.y = ca * pond * sin(ang) + Q[i].y;

                if(abs(round(aux.x) - aux.x) < EPS && abs(round(aux.y) - aux.y) < EPS && abs(round(aux.x)) <= 100 && abs(round(aux.y)) <= 100 && grid[ll(round(aux.x)) + 100][ll(round(aux.y)) + 100])
                {
                    ans ++;
                }

                ang = base + ang2;
                if(ang >= 2 * PI) ang -= 2* PI;
                aux.x = bc * pond * cos(ang) + Q[i].x;
                aux.y = bc * pond * sin(ang) + Q[i].y;

                if(abs(round(aux.x) - aux.x) < EPS && abs(round(aux.y) - aux.y) < EPS && abs(round(aux.x)) <= 100 && abs(round(aux.y)) <= 100 && grid[ll(round(aux.x)) + 100][ll(round(aux.y)) + 100])
                {
                    ans ++;
                }


                ang = base - ang1;
                if(ang < 0) ang += 2* PI;
                aux.x = ca * pond * cos(ang) + Q[i].x;
                aux.y = ca * pond * sin(ang) + Q[i].y;

                if(abs(round(aux.x) - aux.x) < EPS && abs(round(aux.y) - aux.y) < EPS && abs(round(aux.x)) <= 100 && abs(round(aux.y)) <= 100 && grid[ll(round(aux.x)) + 100][ll(round(aux.y)) + 100])
                {
                    ans ++;
                }

                ang = base - ang2;
                if(ang < 2 * PI) ang -= 2* PI;
                aux.x = bc * pond * cos(ang) + Q[i].x;
                aux.y = bc * pond * sin(ang) + Q[i].y;

                if(abs(round(aux.x) - aux.x) < EPS && abs(round(aux.y) - aux.y) < EPS && abs(round(aux.x)) <= 100 && abs(round(aux.y)) <= 100 && grid[ll(round(aux.x)) + 100][ll(round(aux.y)) + 100])
                {
                    ans ++;
                }
                
            }
        }
        cout << ans / mult << "\n";
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
