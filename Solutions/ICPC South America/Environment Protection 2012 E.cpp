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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3973
int main() {

  
  db W, D, A, K, x;
  
  while(cin >> W >> D >> A >> K)
  {
    
    vector<db> p1,q1,p2,q2;
    for(int i = 0; i < K + 1; i++)
    {
      cin>>x;
      p1.push_back(x);
    }
    for(int i = 0; i < K + 1; i++)
    {
      cin>>x;
      q1.push_back(x);
    }
    for(int i = 0; i < K + 1; i++)
    {
      cin>>x;
      p2.push_back(x);
    }
    for(int i = 0; i < K + 1; i++)
    {
      cin>>x;
      q2.push_back(x);
    }
    db l = -D,r = 0, x1, x2, s1, s2, v, p, ans, area = 0;

    for(int ww=0;ww<=35;ww++)
    {
        area = 0;
        p=(l+r)/2.0;
        for(db i = 0.00005 * W; i <= W; i+= 0.0001*W)
        {
          x1 = 0; x2 = 0; s1 = 0; s2 = 0, v = 1;
          db u, d;
          for (int j = 0; j < K + 1; j++)
          {
            x1 += v * p1[j];
            x2 += v * p2[j];
            s1 += v * q1[j];
            s2 += v * q2[j];
            v *= i;
          }
          u = max(x1/s1, p);
          d = max(x2/s2, p);
          area += (u-d);
        }
        area *= 0.0001*W;
        if(area >= A)
        {
          l = p;
          ans = p;
        }
        else r = p;
    }
    cout<<fixed<<setprecision(5)<<-ans<<"\n";
    
  }
}
