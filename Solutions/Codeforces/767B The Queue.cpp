#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://codeforces.com/problemset/problem/767/B

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
  ll ts, tf, t, ti;
  cin >> ts >> tf >> t;
  ll n;
  cin >> n;
  priority_queue<pll,vector<pll>,greater<pll> >q;
  q.push({tf - t, 3});
  q.push({ts, 0});
  q.push({tf, 0});
  ll cola = 0, t_libre = ts;
  bool activo = 0;
  for(int i = 0; i < n; i++)
  {
    cin >> ti;
    if(t - 1 >= 0)
    {
      q.push({ti - 1, 3});
    }
    q.push({ti, 2});
  }
  ll mini = INF, ans = -1;
  while(!q.empty())
  {
    ti = q.top().first;
    ll in = q.top().second;
    q.pop();
    if(in == 0)
    {
      activo = !activo;
      if(cola)
      {
        cola--;
        q.push({ti + t,1});
        t_libre = ti + t;
      }
      if(!activo)break;
    }
    else if(in == 1)
    {
      if(cola)
      {
        q.push({ti + t, 1});
        t_libre = ti + t;
        cola--;
      }
    }
    else if(in == 2)
    {
      if(t_libre <= ti)
      {
        q.push({ti + t, 1});
        t_libre = ti +t;
      }
      else cola++;
    }
    else
    {
      
      if(mini > t * cola + max(0LL, t_libre - ti) && ti + t * cola + max(0LL, t_libre - ti) + t <= tf)
      {
        mini = t * cola + max(0LL, t_libre - ti);
        ans = ti;
      }
    }
    
  }
  cout<<ans<<"\n";
  return 0;
}
