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
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

ll n;
vp ans, pre;
bool o = 0;
vp k, d;
vl vk, vd;
void back(ll in)
{
	if(o)return;
	if(in == n )
	{
		o = 1;
		ans = pre;
		return;
	}
	

	for(ll i = 0; i < n; i++)
	{
		if(!vk[i])
		{
			vk[i] = 1;
			vp s;
			for(int j = 0; j < n+1; j++)
			{
				if(!vd[j])
				{
					ll co = abs(k[i].first - d[j].first) * abs(k[i].first - d[j].first) + abs(k[i].second - d[j].second) * abs(k[i].second - d[j].second);
					s.push_back({co, j});
				}
			}
			sort(ALLR(s));
			ll ini = s.back().first;
			bool o2 = 0;
			vl poss;
			while(!s.empty() && s.back().first == ini)
			{
				poss.push_back(s.back().second);
				s.pop_back();
			}
			//cout << poss.size() << " " << o2 << " "<<in << endl;


			for(int j = 0; j < poss.size(); j++)
			{
				if(poss[j] == 0) continue;
				vd[poss[j]] = 1;
				pre.push_back({i+1, poss[j]+1});
				back(in+1);
				if(o) return;

				pre.pop_back();
				vd[poss[j]] = 0;
			}
			vk[i] = 0;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);

  
	ll t;
	cin >> t;
	for(int T = 1; T <= t; T++)
	{
		ans.clear();
		pre.clear();
		cin >> n;
		vk.assign(n, 0);
		vd.assign(n+1, 0);
		k.clear();
		d.clear();
		ll x, y;
		for(int i = 0; i < n; i++)
		{
			cin >> x >> y;
			k.push_back({x, y});
		}
		for(int i = 0; i < n+1; i++)
		{
			cin >> x >> y;
			d.push_back({x, y});
		}
		o = 0;
		back(0);
		if(o)
		{
			cout << "Case #" << T << ": POSSIBLE\n";
			for(int i = 0; i < ans.size(); i++)
			{
				cout << ans[i].first << " " << ans[i].second << "\n";
			}
		}
		else
		{
			cout << "Case #" << T << ": IMPOSSIBLE\n";
		}
	
	}
		
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}