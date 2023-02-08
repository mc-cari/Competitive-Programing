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

//https://open.kattis.com/problems/importspaghetti

ll p[500][500];
vector<string> ans, names;
void printPath(int i, int j)
{
    if(i != j) printPath(i, p[i][j]);
    ans.push_back(names[j]);
    
 
}
int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<vl > g(n, vl(n, INF));
    string s;
    unordered_map<string, ll> m;
    for(int i = 0; i < n; i++)
    {
        g[i][i] = INF;
        cin >> s;
        m[s] = i;
        names.push_back(s);
    }
    for(int i = 0; i < n; i++)
    {
        ll k, in;
        cin >> s >> k;
        in = m[s];
        for(int j = 0; j < k; j++)
        {
            string s2;
            cin >> s2;
            while(1)
            {
                cin >> s2;
                if(s2.back() != ',')
                {
                    g[in][m[s2]] = 1;
                    break;
                }
                s2.pop_back();
                g[in][m[s2]] = 1;
                    
            }
        }
        
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            p[i][j] = i;
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)

                if(g[i][k] + g[k][j] < g[i][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                    p[i][j] = p[k][j];
                    
                }
    ll mini = INF, in = -1;
    for(int i = 0; i < n; i++)
    {
        if(g[i][i] < mini)
        {
            mini = g[i][i];
            in = i;
        }
    }
    if(mini == INF)
    {
        cout << "SHIP IT\n";
        return 0;
    }
    bool o = 0;
    for(int i = 0; i < n; i++)
    {
        if(g[in][i] + g[i][in] == mini)
        {
            printPath(i, in);
            ans.pop_back();
            printPath(in, i);
            ans.pop_back();
            o = 1;
            break;
            
        }
    }
    if(!o) ans.push_back(names[in]);
    
    
    for(int i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
        if(i < ans.size() - 1)cout << " ";
        else cout << "\n";
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
