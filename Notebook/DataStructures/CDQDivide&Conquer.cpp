#include "../Header.cpp"

//https://robert1003.github.io/2020/01/31/cdq-divide-and-conquer.html

struct Pt {
  int x, y, z, i;
};

const int N = (int)1e5 + 5;

struct BIT {
  int b[N], n;

  void init(int _n) {
    n = _n;
    for(int i = 0 ; i <= n ; ++i) b[i] = 0;
  }
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, int v) {
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  int query(int x) {
    int ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
} bit;

vector<Pt> v;
int n, ans[N];

void cdq(int l, int r) {
  if(l + 1 == r) return;
  int m = (l + r) >> 1;
  cdq(l, m); cdq(m, r);
  int a = l, b = m, sum = 0;
  // need to record the modifications on BIT in order to reset it. The complexity will be $O(N^2)$ if we resetting it brute-forcely.
  vector<int> record;
  // temporary array for merge sort
  vector<Pt> tmp;
  while(a < m && b < r) {
    if(v[a].y > v[b].y) bit.update(v[a].z, 1), sum++, record.push_back(v[a].z), tmp.push_back(v[a++]);
    else ans[v[b].i] += sum - bit.query(v[b].z), tmp.push_back(v[b++]);
  }
  while(a < m) tmp.push_back(v[a++]);
  while(b < r) ans[v[b].i] += sum - bit.query(v[b].z), tmp.push_back(v[b++]);
  for(int i = l ; i < r ; ++i) v[i] = tmp[i - l];
  // reset BIT
  for(auto i : record) bit.update(i, -1);
  // release used memory
  vector<int> ().swap(record);
  vector<Pt> ().swap(tmp);
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    int a, b, c; cin >> a >> b >> c;
    v.push_back({a, b, c, i});
  }
  bit.init(n);
}
void solve() {
  // As we require > not >=
  sort(v.begin(), v.end(), [&](auto a, auto b) { 
      return (a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x > b.x); 
  }); 
  cdq(0, n);
  for(int i = 0 ; i < n ; ++i) cout << ans[i] << '\n';
}

// Personal Implementation

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
ll cdq_div_conq(ll n, ll l, ll r, vector<Node>& v, vector<Node>& aux)
{
	if(l == r)
	{
		aux.pb(v[l]);
		return 0;
	}
	vector<Node> L, R, Z_ord;
	ll ans = cdq_div_conq(2*n,l,(l+r)/2,v, L) + cdq_div_conq(2*n+1,(l+r)/2+1,r,v, R);

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