#include "../Header.cpp"
// Match the preferences of N clients and M restaurants that no side prefer another 
// restaurant or client, respectively.

// hospital-residents variation of stable matching
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll n, m, k, x;
	cin >> n >> m;

	vl cap(m, 1), match(n, -1);

	vector<queue<ll>>pref(n);
	queue<ll> q;
	for(auto &it : cap) cin >> it; // capacity
	
	for(int i = 0; i < n; i++)
	{
		q.push(i);
		cin >> k;
		while(k--)
		{
			cin >> x;
			pref[i].push(x-1); //client preference list
		}
	}

	vector<unordered_map<ll, ll>> res_pref(m);
	for(int i = 0; i < m; i++)
	{
		ll id = 0;
		cin >> k;
		while(k--)
		{
			cin >> x;
			res_pref[i][x-1] = -id; // restaurant preference list
			id++;
		}
	}
		
	vector<set<pll>> in_res(m);
	while(!q.empty())
	{
		ll cl = q.front();
		q.pop();

		ll rest = pref[cl].front(); // actual preference restaurant

		in_res[rest].insert({res_pref[rest][cl], cl});// add client to restaurant
		match[cl] = rest;
		pref[cl].pop(); // remove client preference

		if(cap[rest] == 0)
		{
			ll cl_new = (*in_res[rest].begin()).second; // erase client with less preference
			in_res[rest].erase(in_res[rest].begin());

			match[cl_new] = -1;
			if(!pref[cl_new].empty()) // add client to queue if he has more preferences
				q.push(cl_new);
		}
		else
			cap[rest]--;	
	}
	for(int i = 0; i < n; i++)
		if(match[i] != -1) cout << i+1 <<" "<<match[i]+1 <<"\n";

}
