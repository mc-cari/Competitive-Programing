#include "../Header.cpp"
struct BIT { 
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

    void add(ll k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
};

struct Node {
	ll x, y, z, col = 0, pos;
};
bool sy(Node a, Node b)
{
	return (a.y <= b.y);
}
bool sz(Node a, Node b)
{
	return (a.z >= b.z);
}
// count number of pairs (x_i, y_i, z_i) <= (x_j, y_j, z_j)
//cdq_div_conquer: influence from L to R
// if there are equal tuples, ans += duplicates * (duplicates - 1) / 2 - duplicates
ll cdq_div_conq(ll n, ll l, ll r, vector<Node>& c, vector<Node>& aux)
{
	if(l == r)
	{
		aux.pb(c[l]);
		return 0;
	}
	vector<Node> L, R, Z_ord;
	ll ans = cdq_div_conq(2*n,l,(l+r)/2,c, L) + cdq_div_conq(2*n+1,(l+r)/2+1,r,c, R);

	rep(i, R.size()) R[i].col = 1;

	aux.resize(r - l + 1);
	merge(ALL(L), ALL(R), aux.begin(), sy); //merge sort by y

	rep(i, aux.size()) //sort inverse by z and save pos in aux vector
	{
		aux[i].pos = i;
		Z_ord.pb(aux[i]);
	}

	sort(ALL(Z_ord), sz);
	BIT bit(r - l + 1);
	for(auto it : Z_ord)
	{
		if(it.col == 1) //update
			bit.add(it.pos+1, 1);
		else if(it.col == 0 && it.pos != r - l){ // count 1s with z >= it.z in y >= it.y range
			ans += bit.rsq(it.pos + 2, r - l + 1);
		}
	}
	rep(i, aux.size()) aux[i].col = 0;
	return ans;	
}


int main(){
	ll n;
	cin >> n;
	vector<Node> c, aux;
	Node t;
	rep(i, n)
	{
		cin >> t.x >> t.y >> t.z;
		c.pb(t);
	}
	cout << cdq_div_conq(n, 0, n-1, c, aux) << endl;
}