#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e8
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://www.spoj.com/problems/VBOSS/

struct SegmentTree
{
	vl ST;
	ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.resize(4*N);
		build(1,0,N-1,A);
	}
	void build(ll n, ll l, ll r, vl &A)
	{
		if(l==r)
		{
			ST[n]=A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		ST[n] = max(ST[2*n],ST[2*n+1]);
	}
	ll query(ll i, ll j, ll v)
	{
		return query(1,0,N-1,i,j, v);
	}
	ll query(ll n, ll l, ll r, ll i, ll j, ll v)
	{

		if(r < i || j < l) return INF;

        if(i <= l && r <= j && ST[n] < v) return INF;
		if(l == r)
        {
            if(ST[n] < v) return INF;
            else return l;
        }
        
        ll ans = query(2*n,l,(l+r)/2,i,j, v);
        if(ans == INF)
        {
            ans = query(2*n+1,(l+r)/2+1,r,i,j, v);
        }

		return ans;
	}
    
	
};


vector<vl>g, g2;


ll memo[30200];
ll dfs(ll in)
{
    if(memo[in] != -1)return memo[in];
    ll ans = 1;
    for(auto it : g[in])ans += dfs(it);
    return memo[in] = ans;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;
    while(t--)
    {
        memset(memo, -1, sizeof(memo));
        ll n, q, s, tall, id;
        vl ids;
        cin >> n >> q;
        vector<tuple <ll, ll, ll> > c;
        vl d;
        for(int i = 0; i < n; i++)
        {
            cin >> id >> s >> tall;
            
            c.push_back({s, tall, id});
        }
        g.assign(n, vl());
        g2.assign(n, vl());
        sort(ALL(c));
        unordered_map<ll, ll> m;
        ll in = 0;
        for(auto it : c)
        {
            ids.push_back(get<2>(it));
            d.push_back(get<1>(it));
            m[get<2>(it)] = in;
            in++;
            
        }
        SegmentTree ST(d);
        for(int i = 0; i < n-1; i++)
        {
            ll b = ST.query(i+1, n-1, d[i]);
            
            
            g2[i].push_back(b);
            g[b].push_back(i);
            
        }
        
        while(q--)
        {
            cin >> s;
            ll f = m[s];
            if(g2[f].empty())cout << "0 ";
            else cout << ids[g2[f][0]] << " ";
            cout << dfs(f)-1<< "\n";
        }
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
