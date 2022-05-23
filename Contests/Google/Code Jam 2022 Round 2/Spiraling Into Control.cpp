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

vector<pll> ne, sh;
ll memo[200000][2], fina = 0;
ll dp(ll in, ll o)
{
	if(in == fina) return memo[in][o] = 0;
	if(memo[in][o] != -1) return memo[in][o];
	ll ans = 0;
	ans = max(dp(ne[in].first, 1) + ne[in].second, dp(sh[in].first, 0) + sh[in].second);
	return memo[in][o] = ans;
}

ll p = 0;
vp pat;
vl c;
unordered_map<ll, ll> mp;
ll dp2(ll in, ll o, ll k)
{
	//cout << in << " " << o <<" "<<p<< " " << k << endl;
	//cout << c[in] << "*" << c[sh[in].first] << " " << c[ne[in].first] << endl;
	//cout << memo[sh[in].first][0] + sh[in].second << " " << memo[ne[in].first][1] + ne[in].second << endl;
	if(in == fina) {
		return (k == 0);
	}
	if(in == fina-1)
	{
		return (k == 1);
	}
	ll ans = 0;
	if(memo[sh[in].first][0] + sh[in].second >= k)
	{
		k -= sh[in].second;
		p++;
		if(sh[in].second == 1)
			pat.push_back({c[in], c[sh[in].first]});
		else
			pat.push_back({c[in], c[sh[in].first] - 1});
		ans = dp2(sh[in].first, 0, k);
	}
	else{
		k -= ne[in].second;
		ans = dp2(ne[in].first, 1, k);
	}
	return ans;
}


int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);

  
	ll t;
	cin >> t;
	for(int T = 1; T <= t; T++)
	{
		memset(memo, -1, sizeof(memo));
		pat.clear();
		p = 0;
		c.clear();
		ll n, k;
		cin >> n >> k;
		ne.assign(2*n, pll(-1, -1)); sh.assign(2*n, pll(-1, -1));
		ll up = 0, down = n-1, left = 0, right = n-1;
		ll dir = 0; // E S W N
		mp.clear();
		ll num = 1, in = 0;
		c.push_back(num);
		mp[num] = 0;
		for(int i = 0; i < 2*n-1; i++)
		{
			ll nex = 0;
			if(dir == 1)
			{
				nex = num + down+1;
				right--;
			}
			else 
			{
				nex = num + right+1;
				down--;
			}

			num = nex;
			mp[num] = i+1;
			fina = i+1;
			c.push_back(num);

			in++;
			dir += 1;
			dir %= 2;
		}
		fina--;
		right = n-1; down = n-1;
		dir = 0;
		num = 1;
		for(int i = 0; i < 2*n-2; i++)
		{

			ll sum = right * 2 + down * 2 - 1;
			ll nex = 0;
			if(dir == 1)
			{
				nex = num + down+1;
				right--;
			}
			else 
			{
				nex = num + right+1;
				down--;
			}
			ne[mp[num]] = {mp[nex], nex - num};
			ll cost = 1;
			if(mp[num + sum ] == 0)
			{
				sum++;
				cost++;
			}
			sh[mp[num]] = {mp[num + sum], cost};
			//cout << num  << " " << num + sum << " "<< cost <<  " "<<nex << " "<< nex - num<< "\n";
			num = nex;


			in++;
			dir += 1;
			dir %= 2;
		}

		dp(0,0);
		//cout << dp(0, 0)<<" "<<fina << "\n";
		in = 0;
		
		
		cout << "Case #" << T << ": ";
		if(dp2(0, 0, k))
		{
			cout << p << "\n";
			for(auto x : pat)
				cout << x.first << " " << x.second << "\n";
		}
		else cout << "IMPOSSIBLE\n";
	}
		
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}