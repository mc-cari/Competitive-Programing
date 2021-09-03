#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e15
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
 
 //https://codeforces.com/group/YjFmW2O15Q/contest/102363/attachments
 
string ans, aux;
vl g;
vector<char> c;
ll n, d;
 


void back(ll in, ll cont)
{

    if(cont == d)
    {
        string aux2 = aux;
        reverse(ALL(aux2));
        ans = max(aux2, ans);
        return;
    }
    if(g[in] == -1)return;
    aux += c[g[in]];
    back(g[in], cont+1);
    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    

    char x;
    ll y;
    cin >> n >> d;
    g.assign(n, -1);
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x);
    }
    for(int i = 0; i < n; i++)
    {
        cin >> y;
        if(y != -1)g[i] = y-1;
    }
    ans.assign(d, '0');
    for(int i = 0; i < n; i++)
    {
        aux = "";
        aux += c[i];
        back(i, 1);
    }
    for(int i = 0; i < d; i++)
    {
        cout << ans[i];
        if(i < d-1)cout << " ";
        else cout << "\n";
    }
    
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}
