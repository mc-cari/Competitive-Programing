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

//https://www.urionlinejudge.com.br/judge/es/problems/view/2013

map<int,int>f;

bool ver(int in)
{
  for(int i=in;i>=0;i--)
  {
    if(f[i])return false;
  }
  return true;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  string s;
  cin>>s;
  vector<int>c, ans(s.size(),-1);
  for (int i=0;i<s.size();i++)
  {
    c.push_back(s[i]-'0');
  }
  f.clear();

  for(int i = 0; i < 10; i++)f[i] = 2;
  bool res = 0;
  for(int i = 0; i < c.size(); i++)
  {
    if (res)
    {
      for(int j=9;j>=0;j--)
      {
        if(f[j])
        {
          f[j]--;
          ans[i]=j;
          break;
        }
      }
    }
    else
    {
      bool o=0;
      for(int j=c[i];j>=0;j--)
      {
        if(f[j])
        {
          f[j]--;
          ans[i]=j;
          if(j<c[i])res=1;
          o=1;
          break;
        }
      }
      if (!o){
        int in = i-1;
        while(c[in]==0||ver(ans[in]-1))
        {
          f[ans[in]]++;
          in--;
        }
        f[ans[in]]++;
        for(int j=ans[in]-1;j>=0;j--)
        {
          if(f[j])
          {
            f[j]--;
            ans[in]=j;
            break;
          }
        }
        res=1;
        i=in;
      }
    }
    
  }
  for(int i=0;i<ans.size();i++)
  {
    if(i==0&&ans[i]==0)continue;
    if(ans[i]!=-1)
      cout<<ans[i];
  }cout<<"\n";

  
}
