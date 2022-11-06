#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF LLONG_MAX
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (ll i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)


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

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));

	ll t;
	cin >> t;
	repx(T, 1, t+1){
		string s;
		cin >> s;
		ll q, ans = 0;
		cin >> q;
		vector<BIT> v(26, BIT(s.size()));
		rep(i, s.size())
		{
			v[s[i]-'a'].add(i+1, 1);
		}
		while(q--){
			ll l, r;
			cin >> l >> r;
			if((r - l)%2 != 0) continue;
			if(l == r) {
				ans++;
				continue;
			}
			ll aux1 = 0, aux2 = 0;
			rep(i, 26){
				aux1 += abs(v[i].rsq(l, (l+r)/2-1) - v[i].rsq((l+r)/2, r));
				aux2 += abs(v[i].rsq(l, (l+r)/2) - v[i].rsq((l+r)/2+1, r));
			}
			if(aux1 == 1 || aux2 == 1)ans++;
		}
		cout << "Case #" << T << ": " << ans << "\n";
	}
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}