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

//https://www.urionlinejudge.com.br/judge/es/problems/view/1325

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin>>t;
  while(t--)
  {
      string c,ans="";
      cin>>c;
      bool o=0;
      for(int i=c.size()-1;i>=0;i--)
      {
          if(i==0)
          {
              ans='m'+ans;
              break;
          }

          if((c[i]=='p'||c[i]=='q')&&!o)
          {
              if(c[i]=='p')ans='s'+ans;
              else ans='r'+ans;
          }
          else if(!o)
          {
              if(c[i]=='s')ans='p'+ans;
              else ans='q'+ans;
              o=1;
          }
          else ans=c[i]+ans;
          
      }
      if(!o)
      {
          cout<<"<none> ";
      }
      else cout<<ans<<" ";

      ans="";
      o=0;
      for(int i=c.size()-1;i>=0;i--)
      {
          if(i==0)
          {
              ans='m'+ans;
              break;
          }

          if((c[i]=='s'||c[i]=='r')&&!o)
          {
              if(c[i]=='s')ans='p'+ans;
              else ans='q'+ans;
          }
          else if(!o)
          {
              if(c[i]=='q')ans='r'+ans;
              else ans='s'+ans;
              o=1;
          }
          else ans=c[i]+ans;
          
      }
      if(!o)
      {
          cout<<"<none> ";
      }
      else cout<<ans<<" ";

      ans="";
      o=0;
      for(int i=c.size()-1;i>=0;i--)
      {
          if(i==0)
          {
              ans='m'+ans;
              break;
          }

          if((c[i]=='p'||c[i]=='s')&&!o)
          {
              if(c[i]=='p')ans='q'+ans;
              else ans='r'+ans;
          }
          else if(!o)
          {
              if(c[i]=='q')ans='p'+ans;
              else ans='s'+ans;
              o=1;
          }
          else ans=c[i]+ans;
          
      }
      if(!o)
      {
          cout<<"<none> ";
      }
      else cout<<ans<<" ";

      ans="";
      o=0;
      for(int i=c.size()-1;i>=0;i--)
      {
          if(i==0)
          {
              ans='m'+ans;
              break;
          }

          if((c[i]=='q'||c[i]=='r')&&!o)
          {
              if(c[i]=='q')ans='p'+ans;
              else ans='s'+ans;
          }
          else if(!o)
          {
              if(c[i]=='p')ans='q'+ans;
              else ans='r'+ans;
              o=1;
          }
          else ans=c[i]+ans;
          
      }
      if(!o)
      {
          cout<<"<none>\n";
      }
      else cout<<ans<<"\n";

      
  }
}
