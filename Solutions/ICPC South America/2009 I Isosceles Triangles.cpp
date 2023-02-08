#include<bits/stdc++.h>
using namespace std;
typedef double ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

//https://www.urionlinejudge.com.br/judge/es/problems/view/1378

struct point { double x, y;   // only used if more precision is needed
  point() { x = y = 0.0; }                      // default constructor
  point(double _x, double _y) {
    x=_x;y=_y;
  }        // user-defined
  bool operator < (point other) const { // override less than operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;          // first criteria , by x-coordinate
    return y < other.y; }          // second criteria, by y-coordinate
    point operator - (point other) const{
        point aux(x-other.x,y-other.y);
        return aux;
    }
  // use EPS (1e-9) when testing equality of two floating points
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS)); } 
  point operator + (point other) const{
      point aux(x+other.x,y+other.y);
      return aux;
  }
  point operator * (db other) const{
      point aux(x*other,y*other);
      return aux;
  }
   };
double dist(point p1, point p2) {                // Euclidean distance
                      // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  while(cin>>n)
  {
    if(n==0)break;
    vector<point>c;
    point a;
    ll ans=0;
    for(int i=0;i<n;i++)
    {
      cin>>a.x>>a.y;
      c.push_back(a);
    }
    for(int i=0;i<n;i++)
    {
      vector<db>d;
      for(int j=0;j<n;j++)
      {
        if(i == j)continue;
        d.push_back(dist(c[i],c[j]));
      }
      sort(ALL(d));
      ll cont=1;
      db prev=d[0];
      for(int j=1;j<d.size();j++)
      {
        if(d[j]!=prev)
        {
          if(cont>=2)
          {
            ans+=cont*(cont-1)/2;
          }
          prev=d[j];
          cont=1;
        }
        else cont++;
      }
      if(cont>=2)
      {
        ans+=cont*(cont-1)/2;
      }
    }
    cout<<ans<<"\n";
  }

  
}
