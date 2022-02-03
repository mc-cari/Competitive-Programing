#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e5
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1712

string joseph(vector<int> &c, ll k, ll pos)
{
    if(c.size() == 1)
    {
        if(c[0] == 1)return "Keka";
        else return "Gared";
    }
    ll in = (pos + k)%c.size();
    ll aux = c[in];
    pos = in+1;
    pos %= c.size();
    c.erase(c.begin() + in);
    

    ll in2 = (pos + k)%c.size();
    if(aux != c[in2])
        c[in2] = 1;
    else c[in2] = 0;
    in2++;
    in2 %= c.size();
    

    return joseph(c, k, (in2+1)%c.size());
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, m, k;
    while(cin >> n >> m >> k && (n + m + k))
    {
        vector<int>c;
        for(int i = 0; i < n; i++)c.push_back(0);
        for(int i = 0; i < m; i++)c.push_back(1);
        cout<<joseph(c, k-1, 0)<<"\n";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

