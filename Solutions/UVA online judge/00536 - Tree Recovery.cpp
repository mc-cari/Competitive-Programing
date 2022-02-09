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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=477

string a, b, c;
vl L, R;
ll n;

void trav(ll l, ll r, ll pos)
{
    ll p, p2;
    for(int i = 0; i < n; i++)
        if(a[i] - 'A' == pos)
            p = i;
    for(int i = l; i <= r; i++)
        if(b[i] - 'A' == pos)
            p2 = i;
    if(p != n-1)
    {
        ll left = a[p+1] - 'A';
        for(int i = l; i < p2; i++)
            if(b[i] - 'A' == left)
            {
                L[pos] = left;
                trav(l, p2-1, left);
                break;
            }
                
    }
    vl ri(26, 0);
    for(int i = p2+1; i <= r; i++)
        ri[b[i] - 'A']++;
    for(int i = p+1; i < n; i++)
    {
        if(ri[a[i] - 'A'] == 1)
        {
            R[pos] = a[i] - 'A';
            trav(p2+1, r, a[i] - 'A');
            break;
        }
    }
    
}

void dfs(ll in)
{
    if(L[in] != -1)
        dfs(L[in]);
    if(R[in] != -1)
        dfs(R[in]);
    c += (char)(in + 'A');
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while(cin >> a >> b)
    {
        L.assign(26, -1);
        R.assign(26, -1);
        c = "";
        n = a.size();
        trav(0, n-1, a[0] - 'A');
        dfs(a[0] - 'A');
        cout << c << "\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}