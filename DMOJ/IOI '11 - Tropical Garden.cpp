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

//https://dmoj.ca/problem/ioi11p1

void count_routes(int n, int m, int p, int R[][2], int q, int G[])
{


    vector<vp> g(n, vp());
    for(int i = 0; i < m; i++) {
        ll a = R[i][0], b = R[i][1];
        
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    vp dest;
    vl nex(2 * n, -1);
    for(int i = 0; i < n; i++)
    {
        ll mini = INF, dest1 = -1, mini2 = INF, dest2 = -1;
        for(auto it : g[i])
        {
            if(mini > it.second)
            {
                mini2 = mini;
                dest2 = dest1;
                mini = it.second;
                dest1 = it.first;
            }
            else if(mini2 > it.second)
            {
                mini2 = it.second;
                dest2 = it.first;
            }
        }
        if(mini2 == INF) dest2 = dest1;
        dest.push_back({dest1, dest2});
        
    }
    
    vector<vl> g2(2*n, vl());
    for(int i = 0; i < n; i++)
    {
        ll u = dest[i].first;
        if(dest[u].first == i)
        {
            g2[u + n].push_back(i);
            nex[i] = u + n;
        }
        else 
        {
            g2[u].push_back(i);
            nex[i] = u;
        }

        u = dest[i].second;
        if(dest[u].first == i) 
        {
            g2[u + n].push_back(i + n);
            nex[i + n] = u + n;
        }
        else 
        {
            g2[u].push_back(i + n);
            nex[i + n] = u;
        }
    }

    vl vis(2 * n, 0), dis(2 * n, INF), vis2(2 * n, 0), dis2(2 * n, INF);
    
    queue<ll> Q;
    Q.push(p);
    dis[p] = 0;
    while(!Q.empty())
    {
        ll k = Q.front(); Q.pop();
        if(vis[k]) continue;
        vis[k] = 1;
        for(auto it : g2[k])
        {
            if(!vis[it])
            {
                dis[it] = min(dis[k] + 1, dis[it]);
                Q.push(it);
            }
        }
    }
    Q.push(p + n);
    dis2[p + n] = 0;
    while(!Q.empty())
    {
        ll k = Q.front(); Q.pop();
        if(vis2[k]) continue;
        vis2[k] = 1;
        for(auto it : g2[k])
        {
            if(!vis2[it])
            {
                dis2[it] = min(dis2[k] + 1, dis2[it]);
                Q.push(it);
            }
        }
    }
    
    bool cycle1 = 0, cycle2 = 0;
    ll tam1 = 0, tam2 = 0;
    ll in = p;
    vis.assign(2 * n, 0);
    while(!vis[in])
    {
        vis[in] = 1;
        tam1++;
        in = nex[in];
    }
    if(in == p) cycle1 = 1;

    in = p + n;
    vis.assign(2 * n, 0);
    while(!vis[in])
    {
        vis[in] = 1;
        tam2++;
        in = nex[in];
    }
    if(in == p + n) cycle2 = 1;


    for(int j = 0; j < q; j++)
    {
        ll k = G[j], ans = 0;
        
        for(int i = 0; i < n; i++)
        {
            if(cycle1)
            {
                if(dis[i] <= k && (k - dis[i]) % tam1 == 0)
                {
                    ans++;
                    continue;
                }
            }
            else
            {
                if(dis[i] == k)
                {
                    ans++;
                    continue;
                }
            }
            if(cycle2)
            {
                if(dis2[i] <= k && (k - dis2[i]) % tam2 == 0)
                {
                    ans++;
                    continue;
                }
            }
            else
            {
                if(dis2[i] == k)
                {
                    ans++;
                    continue;
                }
            }
        }
        answer(ans);

    }

}
int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, p;
    cin >> n >> m >> p;
    int R[m][2];
    for(int i = 0; i < m; i++)
    {
        cin >> R[i][0] >> R[i][1];
    }
    ll q;
    cin >> q;
    int G[q];
    for(int i = 0; i < q; i++)
    {
        cin >> G[i];
    }
    count_routes(n, m, p, R, q, G);
    


    return 0;
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
