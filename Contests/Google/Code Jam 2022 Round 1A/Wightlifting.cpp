#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e9
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)






int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);



    int t;
    cin >> t;
    for(int T = 1; T <= t; T++) {
        int e, w, cont = 0;
        cin >> e >> w;
        vector<vector<int> > v(e, vector<int>());

        vector<tuple<int, int ,int>> ed;
        vector<int>siz;
        int nod = 0, prev = 0, ac = 0;
        for(int i = 0; i < e; i++)
        {
            for(int j = 0; j < w; j++)
            {
                ll x;
                cin >> x;
                while(x--)v[i].push_back(j);
            }
            int a = 0;
             do {
                a++;
                    
            }while(next_permutation(ALL(v[i])));
            siz.push_back(a);
            ac += a;
            
        }
        vector<vector<pair<int,int>> > g(ac + 2, vector<pair<int,int>>());
        
        do {
            nod++;
            g[0].push_back({v[0].size(), nod});
                
        }while(next_permutation(ALL(v[0])));
        prev = 0;
        

        for(int i = 0; i < e-1; i++)
        {
            int aux = prev;
            do {

                aux++;
                int aux2 = prev + siz[i];
                do {
                    aux2++;
                    int sim = 0;
                    for(int j = 0; j < v[i].size() && j < v[i+1].size(); j++)
                    {
                        if(v[i][j] == v[i+1][j])
                            sim++;
                        else break;
                    }
                    g[aux].push_back({int(v[i].size()) + int(v[i+1].size()) - sim*2, aux2});
                } while(next_permutation(ALL(v[i+1])));
                
            }while(next_permutation(ALL(v[i])));
            prev += siz[i];
        }
        
        nod = prev;
        do {
            nod++;
            g[nod].push_back({v.back().size(), ac + 1});
                
        }while(next_permutation(ALL(v.back())));

        vl d(ac+2, INF);
        priority_queue<pll, vp, greater<pll> > q; //from low to high
        ll s, t;
        q.push({0, 0});
        d[0] = 0;
        ll ans;

        while(!q.empty()){

            ll w, u;
            tie(w, u) = q.top();
            q.pop();
            if(u == ac+1)
            {
                ans = w;
                break;
            }
            
            if(w > d[u])continue;
            for(auto it : g[u])
            {
                if(d[it.second] > w + it.first)
                {
                    d[it.second] = w + it.first;
                    q.push({d[it.second], it.second});
                }
            }
        }
        cout << "Case #" << T << ": " << ans << "\n";
    }

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}