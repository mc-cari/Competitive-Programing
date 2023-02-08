#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e9
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (ll i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)


//https://csacademy.com/contest/ieeextreme-practice/task/array

struct BIT { 
    
    /*********All Index starts at 1***********/
    
    vl bit;
    BIT(ll n) { bit.assign(n+1, 0); }

    ll psq(ll k) {
        ll sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }

    ll rsq(ll a, ll b) {
        return psq(b) - psq(a-1);
    }
    

    // increment k'th value by v (and propagate)
    void add(ll k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
    void set(ll k, ll v)
    {
        ll aux = rsq(k,k);
        for (; k < bit.size(); k += (k & -k)) bit[k] += v-aux;
        //bit[idx] = min(bit[idx], val);
    }

    // (1, r)
    ll getmin(ll r) {
        ll ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }
};

vp lft;
vl ans;
ll n, m, p;

bool solve(ll l, ll r, ll k, BIT& bit){

	if(r < l) return false;
	if(lft[r].first == -1){
		lft[r].first = l;
		lft[r].second = k;
		bit.add(r+1, k);
		return 1;
	}
	else{
	
		if(l == lft[r].first){
			return k == lft[r].second;
		}
		else if(l < lft[r].first){
			ll res = (k - lft[r].second + p)%p;
			return solve(l, lft[r].first-1, res, bit);
		}
		else{
			ll res = (lft[r].second - k + p)%p;
			return solve(lft[r].first, l-1, res, bit);
		}
	}
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));


	
	cin >> n >> m >> p;
	vector<tuple<ll, ll, ll>> seg;

	BIT bit(n);

	rep(i, m)
	{
		ll x, y, k;
		cin >> x >> y >> k;
		seg.pb({y-1, x-1, k});

	}

	ans.assign(n, 0);
	lft.assign(n, {-1, -1});
	bool o = 1;
	for(auto it : seg)
	{
		ll y, x, k;
		tie(y, x, k) = it;
		if(!solve(x, y, k, bit)) o = 0;


	}
	if(!o){
		cout << "None\n";
	}
	else{
		rep(i, n){
			if(lft[i].first != -1){
				ll sum = bit.rsq(lft[i].first+1, i+1);
				
				bit.add(i+1, ((lft[i].second - sum + p)%p + p)%p);
			}
			cout << bit.rsq(i+1, i+1)%p << " ";
		}cout << "\n";
	}

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}