#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
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

	ios_base::sync_with_stdio(0);
	cin.tie(0);

    ll n, x;
    vl c;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x-1);
    }
    vl ans(n, 0);
    for(int i = 0; i < n; i++)
    {
        vl freq(n, 0);
        set<ll>s;
        ll maxi = 0;
        for(int j = i; j < n; j++)
        {
            freq[c[j]]++;
            if(freq[c[j]] > maxi)
            {
                maxi = freq[c[j]];
                s.clear();
                s.insert(c[j]);
            }
            else if(freq[c[j]] == maxi)
            {
                s.insert(c[j]);
            }
            ans[*s.begin()]++;
        }
    }
    for(int i = 0; i < n; i++)
    {
        cout << ans[i];
        if(i < n-1) cout << " ";
        else cout << "\n";
    }


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}