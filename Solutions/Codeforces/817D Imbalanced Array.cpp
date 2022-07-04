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


struct BIT { // BIT = binary indexed tree (a.k.a. Fenwick Tree)
    /*

       ********All Index starts at 1**********

    */
    vl bit;
    BIT(ll n) { bit.assign(n+1, 0); }
    // prefix sum query (sum in range 1 .. k)
    ll psq(ll k) {
        ll sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
    // range sum query (sum in range a .. b)
    ll rsq(ll a, ll b) {
        return psq(b) - psq(a-1);
    }
    // (1, r)
    ll getmin(ll r) {
        ll ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    // increment k'th value by v (and propagate)
    void add(ll k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
    void set(ll k, ll v)
    {
        ll aux=rsq(k,k);
        for (; k < bit.size(); k += (k & -k)) bit[k] += v-aux;
        //bit[idx] = min(bit[idx], val);
    }
};


int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);

    ll n, x;
    cin >> n;
    vl c, d, ac(n, 0), ac2(n, 0), f;
    
    ll mini = INF, maxi = -INF;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x);
        mini = min(mini, x);
        maxi = max(maxi, x);
        d.push_back(maxi);
        f.push_back(mini);
    }
    ll cont = 0, cant = 0, cant2 = 0;
    maxi = -1;
    stack<pll> st, st2;


    for(int i = n-1; i >= 0; i--)
    {
        while(!st.empty() && st.top().first <= c[i])
        {
            ll prev = st.top().first;
            ll in = st.top().second;
            
            st.pop();
            if(st.empty())
            {
                cant -= (n - in) * prev;
            }
            else{
                cant -= (st.top().second - in) * prev;
            }
        }
        if(st.empty())
        {
            cant += (n - i) * c[i];
        }
        else{
            cant += (st.top().second - i) * c[i];
        }
        st.push({c[i], i});
        ac[i] = cant;

        while(!st2.empty() && st2.top().first >= c[i])
        {
            ll prev = st2.top().first;
            ll in = st2.top().second;
            
            st2.pop();
            if(st2.empty())
            {
                cant2 -= (n - in) * prev;
            }
            else{
                cant2 -= (st2.top().second - in) * prev;
            }
        }
        if(st2.empty())
        {
            cant2 += (n - i) * c[i];
        }
        else{
            cant2 += (st2.top().second - i) * c[i];
        }
        st2.push({c[i], i});
        ac2[i] = cant2;
    }
    ll ans = 0;
    mini = INF;

    for(int i = 0; i < n-1; i++)
    {
        ans += ac[i] - ac2[i];
    }
    cout << ans << "\n";
    


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}