#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://www.spoj.com/problems/METEORS/

vl c, ans, goal, acum;
vector<tuple<ll, ll, ll> >q;
ll n, m, k;
vector<vl> pos;

void divv(ll l, ll r, vl& states)
{
    if(l == k-1)r++;
    if(l == r)
    {
        for(auto it: states)
            ans[it] = l;
        return;
    }
    vector<tuple<ll, ll, ll> > Q;
    ll sum = 0;
    for(int i = l; i <= (l+r)/2; i++){
        ll L, R, a;
        tie(L, R, a) = q[i];
        Q.push_back(make_tuple(L, 0, a));
        Q.push_back(make_tuple(R, 2, -a));
        if(L > R)sum += a;
    }
    for(auto it: states)
    {
        acum[it] = 0;
        for(auto ot: pos[it])Q.push_back(make_tuple(ot, 1, 0));
    }
    
    sort(ALL(Q));
    
    for(int i = 0; i < Q.size(); i++)
    {
        ll in, tipe, v;
        tie(in, tipe, v) = Q[i];
        if(tipe != 1)sum += v;
        else{
            acum[c[in]-1] += sum;
            if(acum[c[in] - 1] > 1e9)acum[c[in]-1] = 1e9;
        }
    }
    if(l == k-1)
    {
        for(auto it: states)
        {
            if(goal[it] <= acum[it])
                ans[it] = k-1;
            else
                ans[it] = -1;
            
        }
    }
    else
    {
        vl ls, rs;
        for(auto it: states)
        {
            if(goal[it] <= acum[it]){
                ls.push_back(it);
            }
            else
            {
                rs.push_back(it);
                goal[it] -= acum[it];
            }
            
        }
        divv(l, (l+r)/2, ls);
        divv((l+r)/2+1, r, rs);
    }
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll x;
    cin >> n >> m;
    ans.resize(n);
    pos.assign(n, vl(0));
    for(int i = 0; i < m; i++)
    {
        cin >> x;
        c.push_back(x);
        pos[x-1].push_back(i);
    }
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        goal.push_back(x);
    }

    
    cin >> k;
    for(int i = 0; i < k; i++)
    {
        ll l, r, a;
        cin >> l >> r >> a;
        l--; r--;
        q.push_back(make_tuple(l, r, a));
    }
    vl states;
    for(int i = 0; i < n; i++)
    {
        states.push_back(i);
    }
    acum.resize(n);
    divv(0, k-1, states);
    for(int i = 0; i < n; i++)
    {
        if(ans[i] == -1)
            cout<<"NIE\n";
        else cout<<ans[i]+1<<"\n";
    }
    return 0;
}
