#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e9
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
//https://codeforces.com/gym/101889/attachments
ll M = 1e9 + 7;

struct SA {
    int n; vector<int> counts, rank, rank_, sa, sa_, lcp; // lcp is optional
    inline int gr(int i) { return i < n ? rank[i]: 0; }
    void csort(int maxv, int k) {
        counts.assign(maxv+1, 0);
        rep(i,0,n) counts[gr(i+k)]++;
        rep(i,1,maxv+1) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_[--counts[gr(sa[i]+k)]] = sa[i];
        sa.swap(sa_);
    }
    void get_sa(vector<int>& s) {
        rep(i,0,n) sa[i] = i;
        sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });
        int r = rank[sa[0]] = 1;
        rep(i,1,n) rank[sa[i]] = (s[sa[i]] != s[sa[i-1]]) ? ++r : r;
        for (int h=1; h < n and r < n; h <<= 1) {
            csort(r, h); csort(r, 0); r = rank_[sa[0]] = 1;
            rep(i,1,n) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    gr(sa[i]+h) != gr(sa[i-1]+h)) ++r;
                rank_[sa[i]] = r;
            } rank.swap(rank_);
        }
    }
    // LCP construction in O(N) using Kasai's algorithm
    // reference: https://codeforces.com/blog/entry/12796?#comment-175287
    void get_lcp(vector<int>& s) { // lcp is optional
        lcp.assign(n, 0); int k = 0;
        rep(i,0,n) {
            int r = rank[i]-1;
            if (r == n-1) { k = 0; continue; }
            int j = sa[r+1];
            while (i+k<n and j+k<n and s[i+k] == s[j+k]) k++;
            lcp[r] = k;
            if (k) k--;
        }
    }
    SA(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_.resize(n);
        sa.resize(n); sa_.resize(n);
        get_sa(s); get_lcp(s); // lcp is optional
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    

    ll n, k, v;
    cin >> n;
    vector<int> s;
    vector<vl> g(n, vl());
    vl siz;
    for(int i = 0; i < n; i++)
    {
        cin >> k;
        siz.push_back(k);
        for(int j = 0; j < k; j++)
        {
            cin >> v;
            g[i].push_back(v);
            s.push_back(v);
        }
        s.push_back(301);
    }
    SA sa(s);
    vl inv(s.size(), 0);
    for(int i = 0; i < s.size(); i++)
        inv[sa.sa[i]] = i;

    ll prev = 0;
    priority_queue<pll, vp, greater<pll>> pq;
    for(int i = 0; i < n; i++)
    {
        pq.push({inv[prev], i});
        prev += siz[i] + 1;

    }
    ll ans = 0;
    while(!pq.empty())
    {
        ll pos = pq.top().first;
        ll idx = pq.top().second;
        pq.pop();
        ans += g[idx][(ll)g[idx].size() - siz[idx] ];
        ans %= M;
        siz[idx]--;
        if(siz[idx] > 0)
        {
            pq.push({inv[sa.sa[pos]+1], idx});
        }
        


        ans *= 365;
        ans %= M;
        
    }
    cout << ans << "\n";

    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
