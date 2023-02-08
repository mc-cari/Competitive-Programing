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
#define PI acos(-1.0) 

//https://www.spoj.com/problems/DINOSM/

struct point { double x, y;   // only used if more precision is needed
  point() { x = y = 0.0; }                      // default constructor

   };

double dist(point& p1, point& p2) {                // Euclidean distance
                      // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); }               // return double
struct UF{
    vector<int>p,r;
    UF(int n)
    {
        r.assign(n,0);
        for(int i=0;i<n;i++)
        {
            p.push_back(i);
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
  int n;
  db W,H;
  while(cin>>n>>W>>H){
    if(n==-1&&W==-1&&H==-1)break;
    vector<point>Q;
    point a;
    for(int i=0;i<n;i++)
    {
      cin>>a.x>>a.y;
      Q.push_back(a);
    }
    db l=1,r=min(H,W),R, ans;
    for(int e=0;e<40;e++)
    {
        R=(l+r)/2.0;
        UF C(n+2);
        bool o=1;
        for(int i=0;i<n&&o;i++)
        {
          for(int j=0;j<i&&o;j++)
          {
            if(dist(Q[i],Q[j])<=2*R){

              C.join(i,j);
            }
            
          }
          if(Q[i].x-R<=0||Q[i].y+R>=H)
          {
            C.join(i,n);
          }
          if(Q[i].x+R>=W||Q[i].y-R<=0)
          {
            C.join(i,n+1);
          }
          if(C.find(n)==C.find(n+1))
          {
            o=0;
            break;
          }
          
        }
        if(o)l=R;
        else 
        {
          ans=R;
          r=R;
        }
    }
    cout<<fixed<<setprecision(3)<<ans<<"\n";
  }

  
}
