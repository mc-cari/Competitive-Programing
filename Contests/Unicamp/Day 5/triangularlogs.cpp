#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
ll block;

struct Query
{
		int L, R, id, ylow, yhigh;
};
bool cmp(Query a, Query b){
		if(a.L / block != b.L / block)
				return a.L < b.L;
		return a.L / block % 2 ? a.R < b.R : a.R > b.R;
}

vl ans;

vl inX;
vl trees;
vector<pair<int, int>> pos;
multiset<pair<int, int>> treesQ;

void add(ll x){

		if(inX[x] != -1){
			treesQ.insert({pos[inX[x]].second, trees[inX[x]]});				
		}
}

void remove(ll x){
		if(inX[x] != -1){
			assert(treesQ.find({pos[inX[x]].second, trees[inX[x]]}) != treesQ.end());
			treesQ.erase(treesQ.find({pos[inX[x]].second, trees[inX[x]]}));
		}
}

bool canFormTriangle(ll a, ll b, ll c) {
     return (a + b > c) && (a + c > b) && (b + c > a); }

vector<tuple<ll, ll, ll>> ordx;
void Mo(vector<Query>& q){
		block = (int)sqrt(ordx.size());
		ans.assign(q.size(), 1);

		sort(q.begin(), q.end(), cmp);
		ll cL = 0, cR = 0;

		for(int i = 0; i<q.size(); i++){
				int L = q[i].L, R=q[i].R;

				while(cR <= R) {
						add(cR);
						cR++;
				}
				while(cL > L) {
						add(cL-1);
						cL--;
				}
				while(cR > R+1) {
						remove(cR-1);
						cR--;
				}
				while(cL < L) {
						remove(cL);
						cL++;
				}

				bool o = 1;

				//cout << q[i].L+1 << " " << q[i].R+1 << " " << q[i].ylow+1 << " " << q[i].yhigh+1 << endl;
				

				ll cont = 0;
				auto it = treesQ.lower_bound( {q[i].ylow, -100});

				vl v;
				for(; it != treesQ.end() && cont < 100; it++) {
						if((*it).first > q[i].yhigh) break;
						cont++;
						v.push_back((*it).second);
						//cout << (*it).second << "\n";

				}
				if(cont < 90){
						o = 0;
						
						sort(v.begin(), v.end());
						for(int j = 2; j < v.size(); j++){
								if(canFormTriangle(v[j], v[j-1], v[j-2])){
										o = 1;
								}
						}
				}
				ans[q[i].id] = o;
		}

}

int main() {
		ios::sync_with_stdio(0);
		cin.tie(0);
	
		ll n, q;
		cin >> n >> q;
		
		ans.assign(q, 0);
		

		for(int i = 0; i < n; i++){
				ll x, y, h;
				cin >> x >> y >> h;
				pos.push_back({x, y});
				trees.push_back(h);
				ordx.push_back({x, 1, i});
	
		}
		vector<Query> queries;

		for(int i = 0; i < q; i++){
				ll xlow, ylow, xhigh, yhigh;
				cin >> xlow >> ylow >> xhigh >> yhigh;
				Query Q;
				Q.L = xlow;
				Q.R = xhigh;
				Q.ylow = ylow;
				Q.yhigh = yhigh;
				Q.id = i;
				queries.push_back(Q);
				ordx.push_back({xlow, 0, i});
				ordx.push_back({xhigh, 2, i});
		}

		sort(ordx.begin(), ordx.end());
		inX.assign(ordx.size(), -1);

		for(int i = 0; i < ordx.size(); i++){

				ll x, t, id;
				tie(x, t, id) = ordx[i];
				if(t == 0){
					queries[id].L = i;
				}
				else if(t == 1){
					pos[id].first = i;
					inX[i] = id;
				}
				else if(t == 2){
					queries[id].R = i;
				}
		}

		Mo(queries); 
		for(auto it : ans) cout <<it << "\n";
}
