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

//https://atcoder.jp/contests/abc128/tasks/abc128_e

int main()
{
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);
  int N,Q,s,t,x;
  cin >> N >> Q;
  priority_queue<tuple<ll, ll, ll>,vector<tuple<ll, ll, ll>>,greater<tuple<ll, ll, ll>> >q;
  for(int i = 0; i < N; i++)
  {
    cin >> s >> t >> x;
    s -= x; t -= x;
    q.push(make_tuple(s, t, x));
  }
  vector<pll> c;
  vl ans(Q,-1);
  for(int i = 0; i < Q; i++)
  {
      cin>>x;
      c.push_back({x,i});
  }
  priority_queue<pll,vector<pll>,greater<pll> >pend;
  multiset<ll> dist;
  ll prev = 0, acum = 0;
  for(int i = 0; i < Q; i++)
  {
      //cout<<i<<endl;
      //cout<<get<0>(q.top())<<" "<<get<1>(q.top())<<" "<<c[i].first<<endl;
      while(!q.empty() && get<0>(q.top()) - c[i].first <= 0)
      {
          if(get<1>(q.top()) - c[i].first > 0)
          {
              pend.push({get<1>(q.top()),get<2>(q.top())});
              dist.insert(get<2>(q.top()));
          }
          q.pop();
      }
      while(!pend.empty() && pend.top().first - c[i].first <= 0)
      {
          dist.erase(dist.find(pend.top().second));
          pend.pop();   
      }
      if(!dist.empty())
      {
          ans[c[i].second] = *dist.begin();
      }
  }
  for(int i = 0; i < Q; i++)
  {
      cout<<ans[i]<<"\n";
  }

}
