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

//https://open.kattis.com/problems/spehrling

deque<char> a1, a2;
ll memo[102][102];
ll dp(ll i, ll j)
{
    
    if(j == a2.size())
    {
        return -(a1.size() - i);
    }
    if(memo[i][j] != -1) return memo[i][j];
    ll ans = INF;

    

    if(i != a1.size())
    {
        if(a1[i] == a2[j])
        {
            return memo[i][j] = dp(i+1, j+1);
        }
        ans = min(ans, dp(i+1, j) -1);
    }
    ans = min(ans, dp(i, j+1) + 1);

    return memo[i][j] = ans;

    
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	

	string s1, s2;
    cin >> s1 >> s2;

    
    ll ans = s1.size() ;

    for(auto it : s1) a1.push_back(it);
    for(auto it : s2) a2.push_back(it);

    while(!a1.empty() && !a2.empty() && a1.front() == a2.front())
    {
        ans--;
        a1.pop_front();
        a2.pop_front();
    }

    memset(memo, -1, sizeof(memo));
    cout << ans*2 + dp(0, 0) << "\n";




    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}