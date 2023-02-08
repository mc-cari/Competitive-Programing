#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://open.kattis.com/problems/246greaaat

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, t, delta = 0;

    cin >> n >> t;
    vp c;
    c.push_back({1, 1});
    for(int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        c.push_back({x, y});
        delta = min(delta, x);
    }
    ll N = t + 1 - delta;
    
    vl d(N, N);

    d[0] = 0;
    vl m(N, 2);
    vp p(N, {-1, -1});
    
    vector<queue<ll> > qs(N+1, queue<ll>());
    qs[0].push(0);
    ll w = 0;
    for(auto q : qs)
    {
        while(!q.empty()){

            ll u = q.front();
            q.pop();

            if(w > d[u])continue;
            ll in = -1;
            for(auto it : c)
            {
                in++;
                ll node = u + it.first;
                if(node < 0 || node > t - delta )continue;
                if(d[node] > d[u] + it.second)
                {
                    d[node] = d[u] + it.second;
                    p[node] = {u, in};
                    qs[d[node]].push(node);
                }
            }
        }
        w++;
    }
	
    vl ans;
    ll in = t;
    while(in != 0)
    {
        ans.push_back(p[in].second);
        in = p[in].first;
    }

    cout << ans.size() << "\n";
    sort(ALL(ans));
    for(int i = 0; i < ans.size(); i++)
    {
        if(i)cout << " ";
        cout << ans[i] + 1;
    } cout << "\n";
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}