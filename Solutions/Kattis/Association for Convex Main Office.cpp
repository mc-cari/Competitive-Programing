#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef ll db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://open.kattis.com/problems/convex

struct point { db x, y;
    point() { x = y = 0.0; } 
    point(db _x, db _y) : x(_x), y(_y) {}
    bool operator < (point other) const {
    return x * other.y - y * other.x  < 0;      
    }
          
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
  }; 

point rotate(point p) {

  return point(p.y, - p.x ); }


int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  set<point> s;
  bool o = 1;
  for (int i = 0; i < INF && o; i++) for(int j = 0; j < i && o; j++) 
  {
      ll k = __gcd(j+1, i-j);
      point p((j+1)/k, (i-j)/k);
      s.insert(p);
      if(s.size() == 100000)o = 0;
  }
  vector<point> Q;
  for(auto p : s) Q.push_back(p);
  for(int i = 0; i < 300000; i++)
    Q.push_back(rotate(Q[i]));
  point ans(0, 20000000);
  ll n;
  cin >> n;
  for(int i = 0; i < n; i++)
  {
      cout<<ans.x<<" "<<ans.y<<"\n";
      ans = ans + Q[i];

  }
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
