#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF LLONG_MAX
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

int main() {
  ll n, m, d, e;
  cin >> n >> m >> d >> e;

  vl cap(m), match(n, -1);
	vector<queue<ll>>pref(n);
	queue<ll> q;

  vp prevv(n, {-1, -1});


  vector<vp> toys(m, vp());

 vector< unordered_map<ll, ll>>played(m);

  rep(i, e){
    ll s, k, t;
    cin >> s >> k >> t;
    //cerr << s << " " << k << " " << t << endl;
    if(t != 0){

      if(prevv[k-1].first != -1){
        
        played[prevv[k-1].second][k-1] += s - prevv[k-1].first;
      }
      if(played[t-1][k-1] == 0){
        pref[k-1].push(t-1);
        cout << "pushing " << t << " to " << k << endl;
      }
      prevv[k-1] = {s, t-1};
    }
    else{
      toys[prevv[k-1].second].pb({s - prevv[k-1].first, k-1});
      played[prevv[k-1].second][k-1] += s - prevv[k-1].first;
      prevv[k-1] = {-1, -1};
    }

  }

  rep(i, n) { 


    q.push(i);
    if(prevv[i].first != -1){
      played[prevv[i].second][i] += d - prevv[i].first;
    }
  }
  rep(i, m){
    for(auto it : played[i]){
      toys[i].pb({it.second, it.first});
    }
  }
  
  

  vector<unordered_map<ll, ll>> res_pref(m);
  rep(i, m){
    sort(ALLR(toys[i]));
    ll id = 0;
    cout << "toys " << i+1 << endl;
    for(auto it : toys[i]){
      res_pref[i][it.second] = -id;
      id++;
      cout << it.second+1 << " " << it.first << endl;
    }
  }

  

  vector<set<pll>> in_res(m);
  while(!q.empty())
	{
		ll cl = q.front();
		q.pop();

		ll rest = pref[cl].front(); // actual preference restaurant

		in_res[rest].insert({res_pref[rest][cl], cl});// add client to restaurant
		match[cl] = rest;
		pref[cl].pop(); // remove client preference

		if(cap[rest] == 0)
		{
			ll cl_new = (*in_res[rest].begin()).second; // erase client with less preference
			in_res[rest].erase(in_res[rest].begin());

			match[cl_new] = -1;
			if(!pref[cl_new].empty()) // add client to queue if he has more preferences
				q.push(cl_new);
		}
		else
			cap[rest]--;	
	}
	for(int i = 0; i < n; i++)
		if(match[i] != -1) cout << i+1 <<"\n";
}