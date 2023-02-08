#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

vl v, s;

void dfs(int t, vector<vl> &g)
{
    v[t] = 1;
    for(auto it : g[t])
        if(!v[it])
            dfs(it, g);
    
    s.pb(t);
}
vl ans;
ll memo[200005], n;
ll check(int in, vector<vl> &g){

	if(in == n-1) return 1;
	if(memo[in] != -1) return memo[in];
	ll sum = 0;
	for(auto it : g[in]){
		if(ans[in] != ans[it]) sum += check(it, g); 
	}
	return memo[in] = sum;
}

int main() {
    
    ll m, k;
    cin >> n >> m >> k;
		
		memset(memo, -1, sizeof memo);
		v.assign(n, 0);
		ll W[n]; 
    vector<vp> g(n, vp());
		vector<vl> g2(n, vl());

    rep(i, n){
        cin >> W[i];
    }
		
    rep(i, m){
        ll u, v;
        cin >> u >> v; u--; v--;
        g[u].pb({W[v], v});
        g[v].pb({W[u], u});
    }

		if(k == 1 && n == 2){
			cout << "impossible\n";
			return 0;
		}
		ans.assign(n, 0);

		for(auto it : g[0]){

			if(it.second == n-1){
				if(k > 1){
					ans[0] = 1;
					ans[n-1] = 1;
					k -= 2;
				}
				for(int i = 1; i < n-1; i++){
					if(k){
						k--;
						ans[i] = 1;
					}
				}
				rep(i, n){
					if(ans[i] == 0)cout << "S";
					else cout << "N";
				}cout << endl;
				return 0;

			}
		}

  vl d(n, INF), d2(n, INF);
	priority_queue<pll, vp, greater<pll> > q;
	q.push({W[0], 0});
	d[0] = W[0];

	while(!q.empty()){
		ll w, u;
		tie(w, u) = q.top();
	    q.pop();
		
		if(w > d[u])continue;
		for(auto it : g[u])
		{
		   	if(d[it.second] > w + it.first)
		   	{
		   		d[it.second] = w + it.first;
		   		q.push({d[it.second], it.second});
			}
	  }
	}

    q.push({W[n-1], n-1});
    d2[n-1] = W[n-1];
    while(!q.empty()){
			ll w, u;
			tie(w, u) = q.top();
				q.pop();
			
			if(w > d2[u])continue;
			for(auto it : g[u])
			{
					if(d2[it.second] > w + it.first)
					{
						d2[it.second] = w + it.first;
						q.push({d2[it.second], it.second});
				}
			}
		}

	set<ll> nodes;
	rep(i, n){
			for(auto it : g[i]){
					if(d[i] + d2[it.second] == d[n-1]){
						nodes.insert(i);
						nodes.insert(it.second);
						g2[i].pb(it.second);
					}
			}
	}
	for(auto it : nodes){
			if(!v[it])
					dfs(it, g2);
	}
	reverse(ALL(s));
	
	for(auto it : s){
		if(!k)break;
			ans[it] = 1;
			k--;
	}
	rep(i, n){
		if(ans[i] == 0 && k){
			ans[i] = 1;
			k--;
		}
	}
	rep(i, n){
		if(ans[i] == 0)cout << "S";
		else cout << "N";
	}cout << endl;

}