#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll m, n, q;
	cin >> m >> n >> q;

	vl nodes(n, 0), pend(n, 0);
	vl Lout(n, -1), Rout(n, -1), Linput(n, -1), Rinput(n, -1); //to outputs
	unordered_map<ll, ll> LoutN, RoutN, LinputN, RinputN; //to nodes
	ll start = 0;
	rep(i, n){
		char t;
		ll x, y, z;
		cin >> t >> x >> y >> z;
		if(t == 'S'){ // x input y,z output
			if(x == 1) start = i;
			nodes[i] = 1;
			Linput[i] = x; 
			LinputN[x] = i;
			LoutN[y] = i;
			RoutN[z] = i;
			Lout[i] = y;
			Rout[i] = z;
			pend[i] = 1;
			
		}
		else{ // x, y input z output
			nodes[i] = 0;
			Linput[i] = x;
			Rinput[i] = y;
			LinputN[x] = i; //input X from L to node
			RinputN[y] = i;
			LoutN[z] = i;
			Lout[i] = z;
			pend[i] = 2;
			
		}
	}

	queue<ll> Q;
	vl tam(n, 0);
	unordered_map<ll, ll> tamOut;
	tam[LinputN[1]] = m;
	Q.push(LinputN[1]);
	while(!Q.empty()){
		ll nod = Q.front();
		Q.pop();

		pend[nod]--;
		if(pend[nod] != 0) continue;

		if(nodes[nod] == 1){ //split
			tamOut[Lout[nod]] += (tam[nod]+1)/2;
			tamOut[Rout[nod]] += tam[nod]/2;
			if(LinputN.count(Lout[nod])){
				ll L = LinputN[Lout[nod]];
				tam[L] += (tam[nod]+1)/2;
				Q.push(L);
			}
			else if(RinputN.count(Lout[nod])){
				ll L = RinputN[Lout[nod]];
				tam[L] += (tam[nod]+1)/2;
				Q.push(L);
			}
			if(RinputN.count(Rout[nod])){
				ll R = RinputN[Rout[nod]];
				tam[R] += tam[nod]/2;
				Q.push(R);
			}
			else if(LinputN.count(Rout[nod])){
				ll R = LinputN[Rout[nod]];
				tam[R] += tam[nod]/2;
				Q.push(R);
			}
	
		}
		else {	
			tamOut[Lout[nod]] += tam[nod];
			if(LinputN.count(Lout[nod])){
				tam[LinputN[Lout[nod]]] += tam[nod];
				Q.push(LinputN[Lout[nod]]);
			}
			else if(RinputN.count(Lout[nod])){
				tam[RinputN[Lout[nod]]] += tam[nod];
				Q.push(RinputN[Lout[nod]]);
			}
		}
		
	}

	while(q--){
		ll x, k, t, node;
		cin >> x >> k;
		if(LoutN.count(x)){
			node = LoutN[x];
			t = 0;
		}
		else{
			node = RoutN[x];
			t = 1;
		}

		if(tamOut[x] < k){
			cout << "none\n";
			continue;
		}

		while(1){
			
			if(nodes[node] == 1){ //split
				if(t == 0) k = k*2-1;
				else k = k*2;
				x = Linput[node];	
			}
			else{ //merge
				assert(t == 0);
				ll LT = tamOut[Linput[node]], RT = tamOut[Rinput[node]];
				if(k <= 2*min(LT, RT)){
					if(k%2 == 1){ // left input
						k = k/2+1;
						x = Linput[node];
					}
					else{ //right input
						k = k/2;
						x = Rinput[node];
					}
				}
				else if(LT > RT){
					k = k - min(LT, RT);
					x = Linput[node];
				}
				else{
					k = k - min(LT, RT);
					x = Rinput[node];
				}
			}
			if(x == 1) break;
			if(LoutN.count(x)){
				t = 0;
				node = LoutN[x];
			}
			else{
				t = 1;
				node = RoutN[x];
			}
		}
		assert(k > 0 && k <= m);
		cout << k << "\n";
	}


	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}