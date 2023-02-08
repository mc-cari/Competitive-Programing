#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

//https://codeforces.com/problemset/problem/471/D
 
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
#define rep(i,a,b) for(ll i=a; i<b; ++i)


// Build longest proper prefix/suffix array (lps) for pattern
// lps[i] = length of the longest proper prefix which is also suffix in pattern[0 .. i]
void init_lps(vl& pattern, ll lps[]) {
    ll n = pattern.size();
    lps[0] = 0; // base case: no proper prefix/suffix for pattern[0 .. 0] (length 1)
    rep(j, 1, n) { // for each pattern[0 .. j]
        ll i = lps[j-1]; // i points to the char next to lps of previous iteration
        while (pattern[i] != pattern[j] and i > 0) i = lps[i-1];
        lps[j] = pattern[i] == pattern[j] ? i+1 : 0;
    }
}

// Count number of matches of pattern string in target string using KMP algorithm
ll count_matches(vl& pattern, vl& target) {
    ll n = pattern.size(), m = target.size();
    ll lps[n];
    init_lps(pattern, lps); // build lps array
    ll matches = 0;
    ll i = 0; // i tracks current char in pattern to compare
    rep(j, 0, m) { // j tracks each char in target to compare
        // try to keep prefix before i as long as possible while ensuring i matches j        
        while (pattern[i] != target[j] and i > 0) i = lps[i-1];
        if (pattern[i] == target[j]) {
            if (++i == n) { // we matched the whole pattern
                i = lps[n-1]; // shift the pattern so that the longest proper prefix/suffix pair is aligned
                matches++;
            }
        }
    }
    return matches;
}



int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

	ll n, w, x;
	cin >> n >> w;
	vl a , b;
	vl c, d;
	for(int i = 0 ; i < n; i++)
	{
		cin >> x;
		c.push_back(x);
		if(i > 0)
		{
			a.push_back(c[i] - c[i-1]);
			
		}
		
	}
	for(int i = 0 ; i < w; i++)
	{
		cin >> x;
		d.push_back(x);
		if(i > 0)
		{
			b.push_back(d[i] - d[i-1]);
			
		}
		
	}
	if(w > n) cout << "0\n";
	else if(w == 1)
	{

		cout << n << "\n";
	}
	else{
		cout << count_matches(b, a) << "\n";
	}
	
	
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
