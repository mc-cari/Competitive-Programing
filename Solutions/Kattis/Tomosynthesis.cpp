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





int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    db x, y, r;
    vector<tuple<db, db, db> > C;
    for(int i = 0; i < n; i++)
    {
        cin >> x >> y >> r;
        C.push_back(make_tuple(x, y, r));

    }
    vector<tuple<db, db, db> >sweep;
    ll libres = n;
    vl sombras(n, 0);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j == i)continue;
            db r1 = get<2>(C[i]), r2 = get<2>(C[j]);
            point c1(get<0>(C[i]), get<1>(C[i]));
            point c2(get<0>(C[j]), get<1>(C[j]));
            db d = dist(c1, c2);
            db d2 = d / (r1 / r2 + 1), d1 = r1 * d2 / r2;
            db a1 = asin(r1 / d1), a2 = asin(r2 / d2);
            point ref(c2 - c1);
            db start = ref.ang() + a1;
            if(start >= 2*PI) start -= 2*PI;
            sweep.push_back(make_tuple(start, 0, i));
            db endd = ref.ang() - a1;
            if(endd < 0)endd += 2*PI;
            sweep.push_back(make_tuple(endd, 1, i));
            if(start < endd)
            {
                if(sombras[i] == 0) libres--;
                sombras[i]++;
            }
        }
    }
    sort(ALL(sweep));
    bool o = 0;
    db prev = 0, res = -1, ans = 0;
    if (libres == n)o = 1;
    for(int i = 0; i < sweep.size(); i++)
    {
        db angg, c, in;
        
        tie(angg, c, in) = sweep[i];

        if(c == 0)
        {
          if(sombras[in] == 1)
          {
            libres++;
            if(libres == n)prev = angg;
          }
          sombras[in]--;
        }
        else if(c == 1)
        {
          if(sombras[in] == 0)
          {
            if(libres == n)
            {
              ans = max(ans, angg - prev);
              if(o)
              {
                o = 0;
                res = prev;
              }
            }
            libres--;
          }
          sombras[in]++;
        }
    }
    if(res != -1 && libres == n)
    {
      ans = max(ans, res + 2*PI - prev);
    }
    cout<<fixed<<setprecision(12)<<ans<<"\n";
    

}
