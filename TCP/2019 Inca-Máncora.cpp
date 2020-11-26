#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e7
#define EPS 0.0000000001
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const db PI = acos(-1.0);

//https://codeforces.com/group/YjFmW2O15Q/contest/102363/attachments

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
   
    ll N, M, Q;
    cin >> N >> M >> Q;
    vector<vector<camb> > cambios(N, vector<camb>(0));
    vector<vector<pair<quer, ll> > > queries(N, vector<pair<quer, ll> >(0));
    for(int i = 0; i < M; i++)
    {
        camb a;
        cin >> a.k >> a.a >> a.b;
        if(a.a > a.b)swap(a.a, a.b);
        cambios[a.b - a.a - 1].push_back(a);
    }
    for(int i = 0; i < Q; i++)
    {
        quer q;
        cin >> q.x >> q.y;
        if(q.x > q.y)swap(q.x, q.y);
        queries[q.y - q.x - 1].push_back({q, i});
    }
    vl ans(Q, 0);
    for(int i = 0; i < cambios.size(); i++)
    {
      vector < tuple <ll, ll, ll> > q;
      for(auto it : cambios[i])
      {
        q.push_back(make_tuple(it.a - 1, 0, 0));
        q.push_back(make_tuple(it.a + it.k - 2, 2, 0));
      }
      for(auto it : queries[i])
      {
        q.push_back(make_tuple(it.first.x - 1, 1, it.second));
      }
      sort(ALL(q));
      ll cont = 0;
      for(auto it : q)
      {
        ll x, tipe, ind;
        tie(x, tipe, ind) = it;
        if(tipe == 0)cont++;
        else if(tipe == 2)cont--;
        else
        {
          if(cont % 2 == 0)ans[ind] = 0;
          else ans[ind] = 1;
        }
        
      }
    }
    for(auto it : ans)
    {
      if(it)cout << "SI\n";
      else cout << "NO\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
