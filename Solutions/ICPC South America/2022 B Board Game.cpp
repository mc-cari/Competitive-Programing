#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()

#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)



typedef ll tc;
struct Line{tc m,h;};
struct CHT { // for minimum (for maximum just change the sign of lines)
	vector<Line> c;
	int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0); // ==ceil(x/y)
	}
	void add(tc m, tc h){ // m's should be non increasing
		Line l=(Line){m,h};
		if(c.size()&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(c.size()>1&&in(c.back(),l)<=in(c[c.size()-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.pb(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	tc eval(tc x){
		// O(log n) query:
		/*int s=0,e=c.size();
		while(e-s>1){int m=(s+e)/2;
			if(fbin(x,m-1))e=m;
			else s=m;
		}
		return c[s].m*x+c[s].h;*/
		// O(1) query (for ordered x's):
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

vector<vl> ans;
vector<pll> lines;
ll T, P;

void search(int l, int r, vector<tuple<ll, ll, ll>> & tokens)
{
	
	if(tokens.size() == 0) return;
	if(l > r) return;

	if(l == r){

		if(l == P-1){
			
			for(auto it : tokens){
				ll x, y, in;
				tie(x, y, in) = it;
				ll y_hull = x * lines[l].first + lines[l].second;
				if(y < y_hull){
					ans[l].pb(in);
				}

			}
		}
		else{
			for(auto it : tokens){
				ll x, y, in;
				tie(x, y, in) = it;
				ans[l].pb(in);
				ll y_hull = x * lines[l].first + lines[l].second;

				
			}
		}
		return;
	}

	ll M = (l+r)/2;
	

	vector<pll> local_lines;
	vector<tuple<ll, ll, ll>> L_tokens, R_tokens;
	repx(i, l, M+1){
		local_lines.pb(lines[i]);
	}
	sort(ALL(local_lines));

	CHT hull;
	for(auto line : local_lines){
		hull.add(-line.first, -line.second);
	}

	for(auto it : tokens){
		ll x, y, in;
		tie(x, y, in) = it;

		ll y_hull = -hull.eval(x);
		if(y < y_hull){
			L_tokens.pb(it);
		}
		else
			R_tokens.pb(it);
	}

	search(l, M, L_tokens);
	search(M+1, r, R_tokens);
}

int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);


	cin >> T;
	vector<tuple<ll, ll, ll>> tokens;
	rep(i, T){
		ll x, y;
		cin >> x >> y;
		tokens.pb({x, y, i});
	}

	
	cin >> P;

	ans.assign(P, vl());

	rep(i, P){
		ll m, c;
		cin >> m >> c;
		lines.pb({m, c});
	}
	sort(ALL(tokens));

	search(0, P-1, tokens);

	for(auto it : ans){
		cout << it.size();
		sort(ALL(it));
		for(auto tok : it){
			cout << " " << tok+1;
		}
		cout << "\n";
	}
	
	return 0;
}
