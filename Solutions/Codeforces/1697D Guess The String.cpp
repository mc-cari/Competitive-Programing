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


int main(){

	//ios_base::sync_with_stdio(0);
	//cin.tie(0);
    
	
	ll n;
	cin >> n;

	vp blocks;

	ll in = 0, q;
	while(in != n)
	{
		ll nex = in+1;

		while(nex != n)
		{
			cout << flush << "? 2 " << in+1 << " " << nex+1 << "\n";
			cin >> q;
			assert(q != 0);
			if(q == 2)break;
			nex++;
		}
		blocks.push_back({in, nex-1});
		in = nex;
	}
	vl type(blocks.size(), 0), vis(blocks.size(), 0);
	ll ch = 2;
	ll prev = 1;
	type[0] = 1;
	vp aps = {{0, 0}};
	for(int i = 1; i < blocks.size(); i++)
	{
		//cout << flush << blocks[i].first << " " << blocks[i].second << "**\n";
		if(prev == 26)
		{
			ll l = 0, r = aps.size()-1, p, res = -1;
			while(l <= r)
			{
				p = (l + r) / 2;
				cout << flush << "? 2 " << aps[p].first+1 << " " << blocks[i].first+1 << "\n";
				cin >> q;
				if(aps.size() - p == q)
				{
					l = p+1;
					res = p;
				}
				else r = p-1;
			}
			//cout << flush << "3 " << p << "\n";
			type[i] = type[aps[res].second];
			aps[res].first = blocks[i].first;
			sort(ALL(aps));
			continue;
		}
		cout << flush << "? 2 " << 1 << " " << blocks[i].first+1 << "\n";
		cin >> q;
		assert(q != 0);
		if(q == prev)
		{
			ll l = 0, r = aps.size()-1, p, res = -1;
			while(l <= r)
			{
				p = (l + r) / 2;
				cout << flush << "? 2 " << aps[p].first+1 << " " << blocks[i].first+1 << "\n";
				cin >> q;
				if(aps.size() - p == q)
				{
					l = p+1;
					res = p;
				}
				else r = p-1;
			}
			//cout << flush << "3 " << p << "\n";
			type[i] = type[aps[res].second];
			aps[res].first = blocks[i].first;
			sort(ALL(aps));


		}
		else 
		{
			type[i] = ch;
			aps.push_back({blocks[i].first, i});

			ch++;
			prev = q;
		}
	}
	vector<char>vis2(28, '0');
	string ans(n, 'a');
	for(int i = 0; i < blocks.size(); i++)
	{
		//cout << i << " " << type[i] << " " << vis2[type[i]] << "\n";
		if(vis2[type[i]] == '0')
		{
			
			cout << flush << "? 1 " << blocks[i].first+1 << "\n";
			char tt;
			cin >> tt;
			vis2[type[i]] = tt;
		}
		for(int j = blocks[i].first; j <= blocks[i].second; j++)
		{
			ans[j] = vis2[type[i]];
		}
	}
	cout << flush << "! " << ans << "\n";

    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
