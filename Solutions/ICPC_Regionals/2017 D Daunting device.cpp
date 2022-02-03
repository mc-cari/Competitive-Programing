#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }

//https://www.urionlinejudge.com.br/judge/en/problems/view/2698

struct cmp{
  bool operator() (tuple<ll,ll,ll> t1, tuple<ll,ll,ll> t2)
  {
    return get<1>(t1) < get<1>(t2);
  }
};


int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll L, C, N;
    while(cin >> L >> C >> N)
    {
      vl col(C, 0);
      col[0] = L;
      set<tuple<ll, ll, ll >, cmp > ord;
      ord.insert(make_tuple(0, L-1, 0));
      for(int i = 0; i < N; i++)
      {
        ll P, X, A, B, S;
        cin >> P >> X >> A >> B;
        S = col[P-1];
        ll m1 = (A + S*S) % L;
        ll m2 = (A + (S+B)*(S+B)) % L;
        ll l = min(m1, m2), r = max(m1, m2);
        auto fi = ord.lower_bound({-1, l, -1}), fin = ord.end();
        pll left = {l - get<0>(*fi), get<2>(*fi)}, rig;
        //cout<<l<<" "<<r<<"*"<<X-1<<" "<<get<1>(*fi)<<" "<<left.second<<"\n";
        for(auto it = fi; it != ord.end(); it++)
        {
          col[get<2>(*it)] -= get<1>(*it) - get<0>(*it) + 1;
          if(get<1>(*it) >= r)
          {
            rig = {get<1>(*it) - r, get<2>(*it)};
            fin = next(it);
            break;
          }
        }

        col[left.second] += left.first;
        col[rig.second] += rig.first;
        ord.erase(fi, fin);
        if(left.first != 0)
        {
          ord.insert(make_tuple(l - left.first, l - 1, left.second));
        }
        if(rig.first != 0)
        {
          
          ord.insert(make_tuple(r + 1, r + rig.first, rig.second));
        }
        ord.insert({l, r, (X-1)});
        col[X-1] += (r - l + 1);
        /*cout<<"\n";
        for(auto it : ord)
        {
          cout<<(get<0>(it))<<" "<<(get<1>(it))<<" "<<(get<2>(it))<<"\n";
        }
        cout<<"\n";*/
      }
      ll maxi = 0;
      for(int i = 0; i < C; i++)
      {
        maxi = max(maxi, col[i]);
      }
      cout<<maxi<<"\n";
    }
      
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
