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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=813

vector<vl> g;
ll in;
vl indegree, vis;
vl sorted;
vector<char> ans;
bool possible;
void toposort()
{
    bool flag = 0;

    for(int i = 0; i < in; i++)
    {
        if(indegree[i] == 0 && !vis[i])
        {
            sorted.push_back(i);
            

            for(auto it : g[i])
                indegree[it]--;
            vis[i] = 1;
            toposort();
            vis[i] = 0;
            sorted.pop_back();

            for(auto it : g[i])
                indegree[it]++;
            flag = 1;
        }
    }
    if(!flag && sorted.size() == in)
    {
        possible = 1;
        for(int i = 0; i < in; i++)
        {
            if(i > 0) cout << " ";
            cout << ans[sorted[i]];
        }
        cout << "\n";
    }
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t, T = 0; cin >> t;
    string line, token;
    getline(cin, line);
    while(t--)
    {
        if(T != 0) cout << "\n";
        T++;
        possible = 0;

        getline(cin, line);
        getline(cin, line);

        stringstream ss(line);
        unordered_map< char, int > m;
        in = 0;
        vector<string>p;
        while( ss >> token)
            p.push_back(token);
 
        sort(ALL(p));
        for(auto it : p)
        {
            m[it[0]] = in;
            in++;
            ans.push_back(it[0]);
        }
        getline(cin, line);
        g.assign(in, vl());
        stringstream s2(line);
        indegree.assign(in, 0);
        vis.assign(in, 0);
        while(s2 >> token)
        {
            g[m[token[0]]].push_back(m[token[2]]);
            indegree[m[token[2]]]++;

        }
        ans.clear();
        toposort();
        if(!possible) cout << "NO\n";

    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
