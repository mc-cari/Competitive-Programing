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

ll nexd[5];
ll nexlapse[5];

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	//next renew day
	nexd[0] = 2;
	nexd[1] = 3;
	nexd[2] = 4;
	nexd[3] = 0;
	nexd[4] = 0;

	// days until next renew
	nexlapse[0] = 30;
	nexlapse[1] = 30;
	nexlapse[2] = 30;
	nexlapse[3] = 32;
	nexlapse[4] = 31;

	string s;
	ll n, x, day, mini = INF;
	cin >> s >> n;
	if(s == "Mon") day = 0;
	else if(s == "Tue") day = 1;
	else if(s == "Wed") day = 2;
	else if(s == "Thu") day = 3;
	else if(s == "Fri") day = 4;
	else if(s == "Sat") day = 5;
	else if(s == "Sun") day = 6;

	for(int i = 0; i < n; i++)
	{
		cin >> x;
		bool o = 0;

		ll xday = ((day - x) % 7 + 7) % 7;

		while(xday != 0) // loop until monday
		{
			x -= nexlapse[xday];
			xday = nexd[xday];
			if(x <= 0)
			{
				mini = min(mini, -x);
				o = 1;
				break;
			}
		}
		if(o)continue;
		
		if(xday == 0 && x == 0)
		{
			mini = min(mini, 30LL);
			continue;
		}

		x %= 91;
		while(x > 0)
		{
			x -= nexlapse[xday];
			xday = nexd[xday];
		}
		mini = min(mini, -x);
		
	}

	cout << mini << "\n";


	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
