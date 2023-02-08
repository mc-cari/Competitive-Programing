#include<bits/stdc++.h>
using namespace std;
typedef double ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
#define EPS 1e-9
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define ALLR(x) x.rbegin() , x.rend()

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1530

struct point { double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}
    point operator - (point other) const{
        point aux(x-other.x,y-other.y);
        return aux;
    }
    point operator + (point other) const{
        point aux(x+other.x,y+other.y);
        return aux;
    }
    point operator * (double other) const{
        point aux(x*other,y*other);
        return aux;
    }
  };      // constructor

int insideCircle(point p, point c, ll r) { // all integer version
  ll dx = p.x - c.x, dy = p.y - c.y;
  ll Euc = dx * dx + dy * dy, rSq = r * r;             // all integer
  return Euc < rSq ? 0 : Euc == rSq ? 1 : 2; } //inside/border/outside

// P1 a

int32_t main()
{
    double N,a,x,y;
    while(cin>>N>>a)
    {
        point r1(0,0),r2(0,a),r3(a,0),r4(a,a),z;
        if(N==0)break;
        vector<point> c;
        ll M=0;
        for(int i=0;i<N;i++)
        {
            cin>>z.x>>z.y;
            if(insideCircle(z,r1,a) < 2 && insideCircle(z,r2,a) < 2 && insideCircle(z,r3,a) < 2 && insideCircle(z,r4,a) < 2)
            {
                M++;
            }
        }
        cout<<fixed<<setprecision(5)<<a*a*(M/N)<<"\n";



    }
}
