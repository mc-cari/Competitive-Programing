#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=4144

#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<vector<int>> g;
    vector<int> count;
    int vocab;
    Trie(int vocab, int maxdepth = 10000) : vocab(vocab) {
        g.reserve(maxdepth);
        g.emplace_back(vocab, -1);
        count.reserve(maxdepth);
        count.push_back(0);
    }
    int move_to(int u, int c) {
        assert (0 <= c and c < vocab);
        int& v = g[u][c];
        if (v == -1) {
            v = g.size();
            g.emplace_back(vocab, -1);
            count.push_back(0);
        }
        count[v]++;
        return v;
    }
    void insert(const string& s, char ref = 'a') {  // insert string
        int u = 0; for (char c : s) u = move_to(u, c - ref);
    }    
    void insert(vector<int>& s) { // insert vector<int>
        int u = 0; for (int c : s) u = move_to(u, c);
    }
    db query(const string& s, char ref = 'a')
    {
      int u = 0; 
      db cost = 0;
      for (char c : s){
        ll co = 0;
        for(auto it : g[u]) if(it != -1)co++;
        
        ll nex = move_to(u, c - ref);
        if(u == 0 || co > 1 || count[u] != count[nex]) cost++;
        u = nex;
        
      }
      return cost;
    }
    int size() { return g.size(); }
};



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    while(cin >> n){
      string s;
      vector<string > c;
      Trie trie(26);
      for(int i = 0; i < n; i++)
      {
        cin >> s;
        c.push_back(s);
        trie.insert(s);
      }
      db sum = 0;
      for(int i = 0; i < n; i++)
      {
        sum += trie.query(c[i]);
      }

      

      cout<<fixed<<setprecision(2)<< sum / db(n) << "\n";
    }
}
