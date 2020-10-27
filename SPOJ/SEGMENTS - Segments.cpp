#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/SEGMENTS/

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, a, b, h;
    cin >> n ;
    
    set<ll> nod;
    ll in = 0;
    unordered_map<ll, ll> m;
    vp segs;
    for(int i = 0; i < n; i++)
    {
      cin >> a >> b >> h;
      segs.push_back({a * 2, b * 2 - 1});
      nod.insert(a * 2); nod.insert(b * 2 - 1);
    }

    for(auto it : nod)
    {

      m[it] = in;
      in++;
    }
    ll l=1 ,r=401 ,p , res = -1;
    while(l<=r)
    {
        p=(l+r)/2;
        vector<vp> g(in + 1, vp(0));
        for(int i = 0; i < in-1; i++)
          g[i+1].push_back({i, 0});
        
        for(int i = 0; i < n; i++){
          g[m[segs[i].first]].push_back({m[segs[i].second], p});
          g[m[segs[i].second]].push_back({m[segs[i].first], -1});
        }

        for(int i = 0; i < in; i++)
          g[in].push_back({i, 0});
        
        vl d(in+1, INF);
        d[in] = 0;
        for(int i=0;i<in;i++)
        {
            bool cyc=0;
            for(int j=0;j < in+1;j++)
                for(int k=0; k < g[j].size(); k++)
                    if(d[j] < INF)

                        d[g[j][k].first]=min(d[g[j][k].first], d[j]+g[j][k].second);
                        cyc=1;

            if(cyc==0)
                break;
        }
        bool cyc=0;//detecta ciclo negativo
        for(int j=0; j < in+1 ;j++)
            for(int k=0;k<g[j].size();k++)
                if(d[j] < INF && d[g[j][k].first] > d[j]+g[j][k].second)
                    cyc=1;


        


        if(cyc)l=p+1;
        else
        { 
          res = p;
          r = p-1;
        }
    }
    cout << res << "\n";
    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
