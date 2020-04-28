#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long long db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
#define double long long //Para usar enteros

//https://www.urionlinejudge.com.br/judge/es/problems/view/2015


double DEG_to_RAD(double d) { return d*PI / 180.0; }

double RAD_to_DEG(double r) { return r*180.0 / PI; }

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
  };



// returns the area
double area(const vector<point> &P) {
  double result = 0;
  for (int i = 0; i < (int)P.size()-1; i++)             // Shoelace formula
    result += (P[i].x*P[i+1].y - P[i+1].x*P[i].y); // if all points are int
  return result; }     // result can be int(eger) until last step


db marea(ll l, ll r, vector<db>& sareas, vector<point>& Q, db atotal)
{
  bool o = 0;
  if(r<l)
  {
    swap(r,l);
  }
  vector<point>aux = {Q[0], Q[l], Q[r], Q[0]};
  db res = sareas[r] - sareas[l] - area(aux);
  return max(res, atotal - res);
}

int main() {
  int n;
  while(cin>>n)
  {
    point a;
    vector<point>Q,aux;
    for(int i=0;i<n;i++)
    {
      cin>>a.x>>a.y;
      Q.push_back(a);
    }
    vector<db> sareas(n+1,0);
    for(int i=2;i<n;i++)
    {
      vector<point>aux = {Q[0], Q[i-1], Q[i], Q[0]};
      sareas[i] = area(aux) + sareas[i-1];
    }
    ll atotal = sareas[n-1];
    ll p2=2, maxi = -1;
    for(int i=0;i<n;i++)
    {
      //if ((i + 1)%n==p2)p2++;
      p2%=n;  
      
      while((p2+2)%n != i && abs(marea(i, (p2+1)%n, sareas, Q, atotal)-(atotal-marea(i, (p2+1)%n, sareas, Q, atotal))) < abs(marea(i, p2, sareas, Q, atotal)-(atotal - marea(i, p2, sareas, Q, atotal))))
      {
        p2++;
        p2%=n;

      }
      ll res = marea(i, p2, sareas, Q, atotal);
      maxi = max(maxi, res);
    }
    cout<<maxi<<" "<<atotal - maxi<<"\n";
  }
  return 0;
}
