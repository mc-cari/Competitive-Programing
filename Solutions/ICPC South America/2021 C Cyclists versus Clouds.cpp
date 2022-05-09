#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef float db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/gym/103640/problem/C

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }

  };
db angle(point a, point o, point b) {  // returns angle aob in rad
  point oa = (a - o), ob = (b - o);
  return acos(oa * ob / sqrt(oa.norm_sq()*ob.norm_sq())); }
bool inPolygon(point pt, const vector<point> &P) {
    if ((ll)P.size() < 3) return false;               // avoid point or line
    db sum = 0;    // assume the first vertex is equal to the last vertex
    for (ll i = 0; i < (ll)P.size()-1; i++) {
      if (((P[i] - pt)^(P[i+1] - pt)) > 0) //CCW check collinear
          sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
      else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
    return fabs(sum) > PI; }   // 360d -> in, 0d -> out, we have large margin


int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll x0, y0, xd, yd;
    cin >> x0 >> y0 >> xd >> yd;

    ll n;
    cin >> n;
    
    vector< vector<point> > Qs;
    vector<char> Qs_dir;
    point p;

    vector<tuple<ll, ll, ll, char, char>> edgev, edgeh;

    for(int i = 0; i < n; i++)
    {
      vector<point> P;
      char c;
      ll v;
      cin >> c >> v;
      for(int j = 0; j < v; j++)
      {
            ll x, y;
            cin >> x >> y;
            p.x = x; p.y = y;

            P.push_back(p);
      }
      P.push_back(P.front());
      for(int j = 1; j <= v; j++)
      {
        ll x = P[j].x, y = P[j].y;
        ll prev = (j - 2 + v+1)%(v+1), nex = (j + 1)%(v+1);
        ll xp = (ll)P[j-1].x, yp = (ll)P[j-1].y;

        char in; //Direccion al interior de la nube respecto de la arista
        if(x != xp)
        {
          if(x > xp) 
          {
            in = 'S';
            if(P[nex].y > y) x++;
            if(P[prev].y > y) xp--;
          }
          else 
          {
            in = 'N';
            if(P[nex].y < y) x--;
            if(P[prev].y < y) xp++;
          }

          edgeh.push_back(make_tuple(min(x, xp), max(x, xp), y, c, in));
        }
        else
        {
          if(y > yp)
          {
            in = 'E';
            if(P[nex].x < x) y++;
            if(P[prev].x < x) yp--;
          } 
          else 
          {
            in = 'W';
            if(P[nex].x > x) y--;
            if(P[prev].x > x) yp++;
          }
          
          edgev.push_back(make_tuple(min(y, yp), max(y, yp), x, c, in));
        }
      }
      
      reverse(ALL(P));
      
      Qs.push_back(P);
      Qs_dir.push_back(c);

    }
    vector<vp> s(102, vp());
    s[0].push_back({x0, y0});

    ll ans = -1;
              //E N  W  S
    vl movx = {1, 0, -1, 0};
    vl movy = {0, 1, 0, -1};

    if(x0 == xd && y0 == yd)
    {
      cout << "0\n";
      return 0;
    }

    vector<vl> D(101, vl(101, -1));
    for(int t = 0; t < 101 && ans == -1; t++)
    {

      while(!s[t].empty() && ans == -1)
      {
        pll u = s[t].back();
        ll xu = u.first, yu = u.second;
        s[t].pop_back();

        if(xu == xd && yu == yd)
        {
          ans = t;
          break;
        }
        
        p.x = u.first; p.y = u.second;
        bool o = 0;
        for(int i = 0; i < n; i++)
        {
          point q = p;
          if(Qs_dir[i] == 'N') q.y -= t;
          else if(Qs_dir[i] == 'S') q.y += t;
          else if(Qs_dir[i] == 'E') q.x -= t;
          else if(Qs_dir[i] == 'W') q.x += t;
          if(inPolygon(q, Qs[i])) 
          {
            o = 1;
            break;
          }
        }
        if(o){

          s[t+1].push_back(u);
          continue;
        }

        // Movimientos disponibles
        vector<bool> disp(4, 1);

        for(auto it : edgev)
        {
          ll y1, y2, x;
          char c, in;
          tie(y1, y2, x, c, in) = it;
          
          if(c == 'W' && in == 'E')
          {
            x -= t;
            if((xu + 1 == x || xu == x) && y2 > yu && y1 < yu) //E
              disp[0] = 0;
            if(xu == x && y2 > yu && y1 <= yu) // N
              disp[1] = 0;
            if(xu == x && y2 >= yu && y1 < yu) // S
              disp[3] = 0;
          }
          else if(c == 'E' && in == 'W')
          {
            x += t;
            if((xu - 1 == x || xu == x) && y2 > yu && y1 < yu) //W
              disp[2] = 0;
            if(xu == x && y2 > yu && y1 <= yu) // N
              disp[1] = 0;
            if(xu == x && y2 >= yu && y1 < yu) // S
              disp[3] = 0;
          }
          else if(c == 'N')
          {
            y1 += t; y2 += t;
            if(in == 'E')
              if(xu == x && y2 >= yu && y1 < yu) // E
                disp[0] = 0;
            if(in == 'W')
              if(xu == x && y2 >= yu && y1 < yu) // W
                disp[2] = 0;
          }
          else if(c == 'S')
          {
            y1 -= t; y2 -= t;
            if(in == 'E')
              if(xu == x && y2 > yu && y1 <= yu) // E
                disp[0] = 0;
            if(in == 'W')
              if(xu == x && y2 > yu && y1 <= yu) // W
                disp[2] = 0;
          }

        }
        for(auto it : edgeh)
        {
          ll x1, x2, y;
          char c, in;
          tie(x1, x2, y, c, in) = it;
          if(c == 'S' && in == 'N')
          {
            y -= t;
            if((yu + 1 == y || yu == y) && x2 > xu && x1 < xu) //N
              disp[1] = 0;
            if(yu == y && x2 > xu && x1 <= xu) // E
              disp[0] = 0;
            if(yu == y && x2 >= yu && x1 < xu) // W
              disp[2] = 0;
          }
          else if(c == 'N' && in == 'S')
          {
            y += t;
            if((yu - 1 == y || yu == y) && x2 > xu && x1 < xu) //S
              disp[3] = 0;
            if(yu == y && x2 > xu && x1 <= xu) // E
              disp[0] = 0;
            if(yu == y && x2 >= yu && x1 < xu) // W
              disp[2] = 0;
          }
          else if(c == 'E')
          {
            x1 += t; x2 += t;
            if(in == 'S')
              if(yu == y && x2 >= xu && x1 < xu) // S
                disp[3] = 0;
            if(in == 'N')
              if(yu == y && x2 >= xu && x1 < xu) // N
                disp[1] = 0;
          }
          else if(c == 'W')
          {
            x1 -= t; x2 -= t;
            if(in == 'S')
              if(yu == y && x2 > xu && x1 <= xu) // S
                disp[3] = 0;
            if(in == 'N')
              if(yu == y && x2 > xu && x1 <= xu) // N
                disp[1] = 0;
          }
          
        }

        bool nx = 0; // Si hay un movimiento bloqueado por una nube nx = 1
        for(int i = 0; i < 4; i++)
        {
            
            ll xn = xu + movx[i], yn = yu + movy[i];
            if(xn > 100 || xn < 0 || yn > 100 || yn < 0) continue;
            

            if(!disp[i] && D[xn][yn] == -1) nx = 1;
            else if(disp[i] && D[xn][yn] == -1)
            {

                D[xn][yn] = t+1;
                s[t+1].push_back({xn, yn});
                if(xn == xd && yn == yd)
                {
                    ans = t+1;
                    break;
                }
            }
        }
        if(nx)
            s[t+1].push_back({xu, yu});


      }
    }
    if(ans == -1)
    {
      ans = 1e9;
      for(auto it : s[101]) // Si ya no hay nubes dentro del mapa, calc dist de manhattan
        ans = min(ans, abs(it.first - xd) + abs(it.second - yd) + 101);
    }
    vector<vl> ver(41, vl(41, 0));

    cout << ans << "\n";
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}