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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1268

int main()
{
  int n;
  while(cin>>n)
  {
    vl c;
    int x;
    for(int i=0;i<n;i++)
    {
      cin>>x;
      c.push_back(x);
    }
    int sum=0;
    for(int i=0;i<n;i++)
    {
      int in,mini=INF;
      for(int j=i;j<n;j++)
      {
        if(c[j]<mini)
        {
          mini=c[j];
          in = j;
        }
      }
      int aux = c[in];
      for(int j=in;j>=i+1;j--)
      {
        c[j]=c[j-1];
      }
      c[i]=aux;
      sum+=in-i;
    }
    cout<<"Minimum exchange operations : "<<sum<<"\n";
  }
}
