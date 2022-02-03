#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

//https://open.kattis.com/problems/undetected

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
point min(point a,point b)
{
    if(a<b)return a;
    return b;
}
point max(point a, point b)
{
    if(!(a<b))return a;
    return b;
}
double dist(point p1, point p2) {                // Euclidean distance
                      // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x-p2.x, p1.y-p2.y); }               // return double
struct UF{
    vector<int>p,r;
    int conjuntos=0;
    UF(int n)//cambiar cuando no es int
    {
        for(int i=0;i<n;i++)
        {
            p.push_back(i);
            r.push_back(0);
        }

    }
    int find(int x)
    {
        if(p[x]==x) return x;
        else return p[x]=find(p[x]);
    }
    void join(int x,int y)
    {
        x=find(x);
        y=find(y);
        if(x!=y)
        {
            if(r[x]>=r[y])
            {
                if(r[x]==r[y])
                {
                    r[x]++;
                }
                p[y]=x;
            }
            else p[x]=y;
        }
    }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n,r;
  cin>>n;
  vector<pair<ll,point>>Q;
  point a;
  for(int i=0;i<n;i++)
  {
    cin>>a.x>>a.y>>r;
    Q.push_back({r,a});
  }
  int k=0;
  //sort(ALL(Q));
  UF C(n+2);
  vl L(n,0),R(n,0);
  bool o=1;
  for(int i=0;i<n&&o;i++)
  {
    if(L[C.find(i)]&&R[C.find(i)])break;
    pair<ll,point>A=Q[i],B;
    for(int j=0;j<i&&o;j++)
    {
      B=Q[j];
      
      if(dist(A.second,B.second)<=A.first+B.first){

        //cout<<i<<" "<<j<<" "<<L[C.find(i)]<<" "<<R[C.find(j)]<<" "<<L[C.find(j)]<<" "<<R[C.find(i)]<<endl;
        
        C.join(i,j);
      }
    }
    if(Q[i].second.x-Q[i].first<=0)
    {
      C.join(i,n);

    }
    if(Q[i].second.x+Q[i].first>=200)
    {
      C.join(i,n+1);
    }
    if(C.find(i)==C.find(n)&&C.find(i)==C.find(n+1))
    {
      o=0;
      break;
    }
    k++;
  }
  cout<<k<<"\n";

  
}
