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
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

void init_lps(vl& s, int lps[]) {
    int n = s.size();
    lps[0] = 0; // base case: no proper prefix/suffix for pattern[0 .. 0] (length 1)
    repx(j, 1, n) { // for each s[0 .. j]
        int i = lps[j-1]; // i points to the char next to lps of previous iteration
        while (s[i] != s[j] and i > 0) i = lps[i-1];
        lps[j] = s[i] == s[j] ? i+1 : 0;

        //optimization to reutilice the lps in O(n)
        if(i > 0 && s[i] == s[lps[i-1]] && lps[i-1] != 0) lps[i-1] = lps[lps[i-1]-1]; 
    }
}


unordered_map<ll, ll> mp;

// Count number of matches of pattern string in target string using KMP algorithm
int kmp(vl& s, vl& t) {
    int n = s.size(), m = t.size();
    int lps[n];
    init_lps(s, lps); // build lps array
    int matches = 0;
    int i = 0; // i tracks current char in pattern to compare
    repx(j, 0, m) { // j tracks each char in target to compare
        // try to keep prefix before i as long as possible while ensuring i matches j        
        while (s[i] != t[j] && i > 0) i = lps[i-1];
        if (s[i] == t[j]) {
            if (++i == n) { // we matched the whole pattern
                i = lps[n-1]; // shift the pattern so that the longest proper prefix/suffix pair is aligned
                mp[j-(n-1)] = 1;
								matches++;
								
            }
        }
    }
    return matches;
}
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll t;
	cin >> t;
	repx(T, 1, t+1){

		ll n, k;
		cin >> n >> k;
		vl a(n), b(n);
		mp.clear();
		rep(i, n) cin >> a[i];
		rep(i, n) cin >> b[i];
		rep(i, n-1) b.pb(b[i]);

		ll matches = kmp(a, b);
		cout << "Case #" << T << ": ";
		if(k == 0){
			if(mp[0])
				cout << "YES\n";
			else
				cout << "NO\n";
			continue;
		}
		/*cout << matches << '\n';
		for(auto it : mp){
			cout << it.first << " ";
		}cout<<'\n';*/
		
		if(matches == 0)
			cout << "NO\n";
		else if(matches >= 2)
			cout << "YES\n";
		
		else {
			if(n == 2){
				if(k % 2 == 0 && mp[0])
					cout << "YES\n";
				else if(k%2 == 1 && mp[0] == 0)
					cout << "YES\n";
				else 
					cout << "NO\n";
			}
			else if(mp[0] == 1 && k == 1)
				cout << "NO\n";
			else
				cout << "YES\n";

		}

		
		
	}
	
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}