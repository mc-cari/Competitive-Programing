#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e7
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://vjudge.net/contest/404967#problem/E

struct point { double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    bool operator == (point other) const {
        return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
    bool operator <(const point &p) const {
        return x < p.x || (abs(x-p.x) < EPS && y < p.y); } 
    point operator + (point other) const{
      point aux(x+other.x,y+other.y);
      return aux;
    }

    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };
struct vec { double x, y;  // name: `vec' is different from STL vector
  vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
  return vec(b.x-a.x, b.y-a.y); }

double dist(point& p1, point& p2) {                // Euclidean distance

  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }


// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double perimeter(vector<point> &P) {
  double result = 0.0;
  for (ll i = 0; i < (ll)P.size()-1; i++)  // remember that P[0] = P[n-1]
    result += dist(P[i], P[i+1]);
  return result; }

// returns the area
double area(const vector<point> &P) {
  double result = 0.0;
  for (ll i = 0; i < (ll)P.size()-1; i++)             // Shoelace formula
    result += (P[i].x*P[i+1].y - P[i+1].x*P[i].y); // if all points are ll
  return fabs(result)/2.0; }     // result can be ll(eger) until last step

double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0; }

double angle(point a, point o, point b) {  // returns angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }
// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
  if ((ll)P.size() < 3) return false;               // avoid point or line
  double sum = 0;    // assume the first vertex is equal to the last vertex
  for (ll i = 0; i < (ll)P.size()-1; i++) {
    if (ccw(pt, P[i], P[i+1]))
         sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
    else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
  return fabs(sum) > PI; }   // 360d -> in, 0d -> out, we have large margin




int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, m, q, contt = 0;
    while(cin >> n >> m >> q){
        
        if(n + m + q  == 0)break;
        if(contt != 0)cout<<"\n";
        contt++;
        
        vector<vector< char> > g(n, vector<char> (m, '.'));
        while(q--)
        {
            char c, c2 = '?', s;
            vector<vector<char> >aux = g;
            vector<point> Q;
            ll x, y, cant;
            
            cin >> c >> x >> y >> cant;
            ll inx = x, iny = y;
            inx--; iny--;
            int flag1 = 0, flag2 = 0, flag3 = 0;
            for(int i = 0; i < cant; i++)
            {
                cin >> s;
                if(inx < 0 || inx >= n || iny < 0 || iny >= m)
                {
                    flag1 = 1;
                    goto end;
                }
                if(aux[inx][iny] != '.' && aux[inx][iny] != c){
                    flag3 = 1;
                    if(c2 == '?')
                    c2 = aux[inx][iny];
                    goto end;
                }
                Q.push_back(point(inx, iny));
                aux[inx][iny] = c;
                if(s == 'B' || s == 'C' || s == 'D')iny++;
                if(s == 'H' || s == 'G' || s == 'F')iny--;
                if(s == 'H' || s == 'A' || s == 'B')inx--;
                if(s == 'F' || s == 'E' || s == 'D')inx++;

            }
            Q.push_back(point(inx, iny));
            
            if(inx < 0 || inx >= n || iny < 0 || iny >= m){
                flag1 = 1; goto end;
            }
            
            if(aux[inx][iny] != '.' && aux[inx][iny] != c){
                flag3 = 1;
                if(c2 == '?')
                c2 = aux[inx][iny];
                goto end;
            }
            if(inx+1 != x || iny+1 != y){
                flag2 = 1; goto end;
            }
            if(flag1 || flag2 || flag3) goto end;

            
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(! inPolygon(point(i, j), Q))continue;
                    if(aux[i][j] != '.' && aux[i][j] != c)
                    {
                        flag3 = 1;
                        if(c2 == '?')
                        c2 = aux[i][j];
                        
                        //goto end;
                    }
                    aux[i][j] = c;
                }
                
            }
            g = aux;
            goto endif;
                
            end:
            if(flag1) cout<<"REGION "<<c<<" GOES OUTSIDE THE ARRAY\n";
            else if(flag2) cout<<"REGION "<<c<<" BOUNDARY IS NOT CLOSED\n";
            else cout<<"REGION "<<c<<" BOUNDARY INTERSECTS REGION "<<c2<<"\n";
            endif:
            int dfdfo;

        }
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cout << g[i][j];
            }cout<<"\n";
        }
        
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
