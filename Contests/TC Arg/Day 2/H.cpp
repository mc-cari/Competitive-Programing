#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

#define rep(i, n) for(int i = 0; i<(int)n; ++i)
ll M = 998244353;
vector<vl>g;

ll dp2(vl& a, vl& b, ll ban)
{
    ll sum = 1;

    rep(i, a.size()){
        if(i == ban) continue;
        sum = ((sum*a[i])%M + (sum*b[i])%M)%M;
    }
    return sum;
}

ll expmod(ll b, ll e)
{
    ll ans = 1;
    while(e){
        if(e&1) ans = ans*b%M;
        b = b*b%M; e >>=1;
    }
    return ans;
}

ll invmod(ll a) { return expmod(a, M-2); }

ll memo[300006][3];
ll dp(ll v, int conected)
{
    if(g[v].size() == 0)
    {
        if(conected == 1)
            return 0;
        else
            return 1;
    }

    if(memo[v][conected] != -1)
        return memo[v][conected];

    ll ans;
    vl con, no;
    for(auto it : g[v])
    {
        con.push_back(dp(it, 1));
        no.push_back(dp(it, 0));
    }
    ll cont = dp2(con, no, -1);

    if(!conected)
    {
        ans = cont;
    }
    else if(conected == 1){
        rep(i, con.size())
        {
            con[i] *=2;
            con[i] %=M;
        }
        cont = dp2(con, no, -1);
        ans = 0;
        rep(i, con.size())
        {
            ans += ((dp(g[v][i], 2 ) * ((cont * invmod((con[i]+no[i])%M))%M ))%M) % M;
            ans %= M;
        }
    }
    else{
        rep(i, con.size())
        {
            con[i] *=2;
            con[i] %=M;
        }
        ans = dp2(con, no, -1);
    }

    return memo[v][conected] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vl> g2(n, vl()); g.assign(n, vl());
    memset(memo, -1, sizeof(memo));

    if(n == 1)
    {
        cout << "1\n";
        return 0;
    }
    rep(i, n-1)
    {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g2[u].push_back(v);
        g2[v].push_back(u);
    }

    stack<int>s;
    vl V(n, 0);
    s.push(0);
    while(!s.empty())
    {
        int v = s.top();
        s.pop();
        if(V[v])continue;
        V[v] = 1;

        for(auto it : g2[v])
        {
            if(!V[it])
            {
                s.push(it);
                g[v].push_back(it);
       
            }
        }
    }   
    cout << (dp(0, 0) + dp(0, 1))%M << "\n";




}