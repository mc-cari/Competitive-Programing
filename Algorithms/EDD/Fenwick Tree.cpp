#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())

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




int main()
{
    vl arr = { 2,4,5,5,6,6,6,7,7,8,9};
    BIT ft(1026);
    for( int i=0;i<11;i++)
    {
        ft.add(i+1,arr[i]);
    }
    cout<<ft.rsq(3,4)<<endl;

}
