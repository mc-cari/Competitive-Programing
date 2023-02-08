#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/contest/163/problem/E

struct BIT {
    vector<int> bit;
    BIT(int n) { bit.assign(n+1, 0); }

    int psq(int k) {
        int sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }

    void add(int k, int v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }

};

struct AC
{
    ll c = 0, ec = 0, M, A, af = -1;
    vector<vl> N, G; vl L, E;
    vl val;
    // L -> suffix link G -> anti L
    // E -> string finish
    AC (ll M, ll A) : M(M), A(A), N(M, vl(A, 0)), G(M, vl()), E(M, 0), L(M, 0), val(M, 0) {}
    ll add(string s) // return endpoint
    {
        af++;
        ll p = 0;
        for (char l : s)
        {
            int t = l - 'a';
            if (!N[p][t]) N[p][t] = ++c;
            p = N[p][t];
        }
        val[p] = 1;
        return p;
    }
    void init()
    {

        queue<int> q; q.push(0); L[0] = -1;
        while (!q.empty())
        {
            int p = q.front(); q.pop();
            for(int c = 0; c < A; c++)
            {
                int u = N[p][c]; if (!u) continue;
                L[u] = L[p] == -1 ? 0 : N[L[p]][c], q.push(u);

                G[L[u]].push_back(u);
            }
            if (p) for(int c = 0; c < A; c++) if (!N[p][c]) N[p][c] = N[L[p]][c];
        }
        
    }
};

vl L, R;
ll in = 1;
void dfs(ll p, AC& ac, BIT& bit)
{
    if(ac.val[p])bit.add(in, 1);
    L[p] = in;
    in++;
    for(auto it : ac.G[p])dfs(it, ac, bit);
    R[p] = in;
    if(ac.val[p])bit.add(in, -1);
    in++;
}
    


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
   ll n, k;
   cin >> n >> k;
   

   vector<string> c;
   vl end, stat(k, 1);
   string s;

   AC ac(1000150, 26);
   for(int i = 0; i < k; i++)
   {
       cin >> s;
       c.push_back(s);
       end.push_back(ac.add(s));
   }
    ac.init();
    BIT bit(2000150);
    L.assign(1000150, 0);
    R.assign(1000150, 0);
    dfs(0, ac, bit);

   for(int i = 0; i < n; i++)
   {
       char z;
       cin >> z;
       ll x;
       if(z == '?')
       {
            cin >> s;
            ll p = 0, ans = 0;
            for (char l : s)
            {
                while(!ac.N[p][l - 'a'] && p != 0)
                    p = ac.L[p];

                if(!ac.N[p][l - 'a'])continue;
                p = ac.N[p][l - 'a'];
                ans += bit.psq(R[p]-1);
            }
            cout<< ans<<"\n";
       }
       else if(z == '-')
       {
           cin >> x;
           if(stat[x-1] == 1){
            stat[x-1] = 0;
            bit.add(L[end[x-1]], -1);
            bit.add(R[end[x-1]], 1);
           }
       }
       else
       {
           cin >> x;
           if(stat[x-1] == 0){
            stat[x-1] = 1;
            bit.add(L[end[x-1]], 1);
            bit.add(R[end[x-1]], -1);
           }
       }
   }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
