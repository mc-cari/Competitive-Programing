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

//https://open.kattis.com/problems/flight

vl ban;
ll n;

pll diam(ll id, vector<vl>& g)
{
    vl d(n, INF), v(n, 0), p(n, -1);
    stack<ll> q;
    d[id] = 0;
    q.push(id);
    while(!q.empty()){

        ll t = q.top();
        q.pop();
        if(v[t]) continue;

        v[t] = 1;
        for(auto it : g[t]){

            if(!v[it] && ban[t] != it)
            {
                d[it] = d[t]+1;
                q.push(it);
            }
        }
    }
    ll maxi = -1, in;
    for(int i = 0; i < n; i++)
    {
        if(!v[i]) continue;
        if(d[i] > maxi)
        {
            maxi = d[i];
            in = i;
        }
    }

    d.assign(n, INF);
    v.assign(n, 0);
    d[in] = 0;
    q.push(in);
    while(!q.empty()){

        ll t = q.top();
        q.pop();
        if(v[t]) continue;

        v[t]=1;
        for(auto it : g[t]){

            if(!v[it] && ban[t] != it)
            {
                p[it] = t;
                d[it] = d[t]+1;
                q.push(it);
            }
        }

    }

    maxi = -1;
    ll in2;

    for(int i = 0; i < n; i++)
    {
        if(!v[i]) continue;
        if(d[i] > maxi)
        {
            maxi = d[i];
            in2 = i;
        }
    }
    ll cont = maxi / 2;
    for(int i = 0; i < cont && p[in2] != -1; i++) in2 = p[in2];

    return {maxi, in2};
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);


    cin >> n;
    vector<vl> g(n, vl());
    ban.assign(n, -1);
    for(int i = 0; i < n-1; i++)
    {
        ll a, b;
        cin >> a >> b; a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vl d(n, INF), p(n, -1), v(n, 0);
    stack <ll> q;
    d[0] = 0;
    q.push(0);
    while(!q.empty()){

        ll t = q.top();
        q.pop();
        if(v[t]) continue;

        v[t] = 1;
        for(auto it : g[t]){

            if(!v[it])
            {
                d[it] = d[t]+1;
                q.push(it);
            }
        }

    }
    ll maxi = -1, in;
    for(int i = 0; i < n; i++)
    {
        if(d[i] > maxi)
        {
            maxi = d[i];
            in = i;
        }
    }
    d.assign(n, INF);
    v.assign(n, 0);
    d[in] = 0;
    q.push(in);
    while(!q.empty()){

        ll t = q.top();
        q.pop();
        if(v[t]) continue;

        v[t] = 1;
        for(auto it : g[t]){

            if(!v[it])
            {
                p[it] = t;
                d[it] = d[t]+1;
                q.push(it);
            }
        }
    }

    maxi = -1;
    ll in2;
    for(int i = 0; i < n; i++)
    {
        if(d[i] > maxi)
        {
            maxi = d[i];
            in2 = i;
        }
    }

    ll mini = INF;
    pll ans1, ans2;
    
    while(p[in2] != -1)
    {
        ban[in2] = p[in2];
        ban[p[in2]] = in2;
        ll d1, d2, p1, p2;
        tie(d1, p1) = diam(in2, g);
        tie(d2, p2) = diam(p[in2], g);
        ll maxi2 = max(d1, d2);
        maxi2 = max(maxi2, (d1 + 1) / 2 + (d2 + 1) / 2 + 1);
        if(mini > maxi2)
        {
            mini = maxi2;
            ans1 = {in2 + 1, p[in2] + 1};
            ans2 = {p1 + 1, p2 + 1};
        }



        ban[in2] = -1;
        ban[p[in2]] = -1;

        in2 = p[in2];
    }
    
    cout << mini << "\n";
    cout << ans1.first << " " << ans1.second << "\n";
    cout << ans2.first << " " << ans2.second << "\n";





    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}