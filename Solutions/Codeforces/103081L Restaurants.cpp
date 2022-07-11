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
#define pb push_back

//https://codeforces.com/gym/103081/problem/L

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, m;
	cin >> n >> m;

	vl cap(m), match(n, -1);
	vector<queue<ll>>pref(n);
	queue<ll> q;
	for(auto &it : cap) cin >> it;
	string line, token;
	getline(cin, line);
	for(int i = 0; i < n; i++)
	{
		q.push(i);
		getline(cin, line);
		stringstream ss(line);
		while(ss >> token)
		{

			pref[i].push(stoi(token)-1);
		}
	}


	vector<unordered_map<ll, ll>> res_pref(m);
	for(int i = 0; i < m; i++)
	{

		getline(cin, line);
		stringstream ss(line);
		ll id = 0;
		while(ss >> token)
		{

			if(token == "0")break;
			res_pref[i][stoi(token)-1] = -id;
			id++;
		}
	}
		
	vector<set<pll>> in_res(m);
	while(!q.empty())
	{
		ll cl = q.front();
		q.pop();

		ll rest = pref[cl].front(); // restaurant

		in_res[rest].insert({res_pref[rest][cl], cl});// add client to restaurant
		match[cl] = rest;
		pref[cl].pop(); // remove client preference

		if(cap[rest] == 0)
		{
			ll cl_new = (*in_res[rest].begin()).second;

			in_res[rest].erase(in_res[rest].begin());
			match[cl_new] = -1;
			if(!pref[cl_new].empty())
				q.push(cl_new);
		}
		else
			cap[rest]--;	
		
		
	}
	for(int i = 0; i < n; i++)
		if(match[i] != -1) cout << i+1 <<"\n";


	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
