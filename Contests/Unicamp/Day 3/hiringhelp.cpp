#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }

};

bool ccw(point p, point q, point r) {
  return ((q - p)^(r - p)) > -EPS; }

multiset<point> convex;
point pp;
ll T = 1;
bool cmp(point a, point b){

  if(b == pp){
    //cout << "hola\n";
  }

  return a*T < b;

}

void add_point(point p){
  //pp = p;
  auto it = convex.lower_bound(p);
  
  //convex.lower_bound()
  vector<point> to_erase;

  auto it2 = it;
  while(it != convex.end() && next(it) != convex.end()){

    if(ccw(p, *it, *next(it))){
      to_erase.pb(*it);
      it++;
    }
    else break;
  }
  it = it2;
  while(it != convex.begin()){

    if(prev(it)->y <= p.y){
      to_erase.pb(*prev(it));
      it--;
    }
    else break;
  }
  for(auto p : to_erase) convex.erase(convex.find(p));
  to_erase.clear();
  convex.insert(p);
}

bool inside(point p){

  pp = p;
  auto it = lower_bound(convex.begin(), convex.end(), p, cmp);

  /*for(auto it2 : convex){
    cout << it2.x << "-" << it2.y << endl;
  }*/
  if(it == convex.begin()){
    
    if(T*(it->y) >= p.y) return true;
    else return false;
  }
  if(it == convex.end()){
    //cout<<"outside"<<endl;
    return false;
  } 

  point p1 = *prev(it);
  point p2 = *it;

  //cout << "inside" << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << endl;
  if(ccw(p1*T, p, p2*T)) return true;
  else return false;
}



int main() {

  ll n;
  cin >> n;

  vector<point> coders;
  rep(i, n){
    point coder;
    cin >> coder.x >> coder.y;
    coders.pb(coder);
  }

  vl sv(n, 1);

  ll e;
  cin >> e;
  vector<tuple<char, ll, ll, ll>> qry;
  vl ans;
  while(e--){
    char c;
    cin >> c;
    if(c == 'c'){
      ll t, l, f;
      cin >> t >> l >> f;
      qry.pb({c, t, l, f});
    }
    else{
      ll i;
      cin >> i;
      sv[i-1] = 0;
      qry.pb({c, i-1, 0, 0});
    }
  }
  
  reverse(ALL(qry));

  bool o = 0;
  rep(i, n){
    if(sv[i]){
      if(o) {
        if(!inside(coders[i]))
          add_point(coders[i]);
      }
      else{
        convex.insert(coders[i]);
        o = 1;
      }
    }
  }


  for(auto it2 : convex){
    //cout << it2.x << "--" << it2.y << endl;
  }
  //return 0;
  for(auto it : qry){
    if(get<0>(it) == 'c'){
      db t = get<1>(it);
      db l = get<2>(it);
      db f = get<3>(it);
      T = t;
      point p(l, f);
      //cout<< p.x << "*" << p.y<<" "<<inside(p) << endl;
      ans.pb(inside(p));
      
    }
    else{
      T = 1;
      ll i = get<1>(it);
      if(o) {
        if(!inside(coders[i]))
          add_point(coders[i]);
      }
      else{
        convex.insert(coders[i]);
        o = 1;
      }
    }

  }
  reverse(ALL(ans));
  for(auto it : ans){
    if(!it) cout << "yes\n";
    else cout << "no\n";
  }
}
       