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


int main(){

	//ios_base::sync_with_stdio(0);
	//cin.tie(0);

	string t;
	cin >> t;

	string s1 = "", s2 = "", s3 = "";

	ll in = 0;
	unordered_map<string, ll> m;

	for(int i = 0; i < 26 && in < t.size(); i++)
		for(int j = 0; j < 26 && in < t.size(); j++)
			for(int k = 0; k < 26 && in < t.size(); k++)
			{
				s1 += char(i + 'a');
				s2 += char(j + 'a');
				s3 += char(k + 'a');

				string aux = {s1.back(), s2.back(), s3.back()};
				m[aux] = in;
				in++;
			}
		


	string a1, a2, a3, ans(t.size(), '0');
	cout << flush <<"? " << s1 << "\n";
	cin >> a1;
	cout << flush <<"? " << s2 << "\n";
	cin >> a2;
	cout << flush <<"? " << s3 << "\n";
	cin >> a3;

	
	for(int i = 0; i < t.size(); i++)
	{
		string aux = {a1[i], a2[i], a3[i]}; 
		ll in2 = m[aux];
		
		ans[in2] = t[i];
	}
	cout << flush << "! " << ans << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}