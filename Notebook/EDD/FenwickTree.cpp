#include "../Header.cpp"

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