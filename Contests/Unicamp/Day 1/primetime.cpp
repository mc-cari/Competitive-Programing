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
#define INF32 INT_MAX
#define EPS 1e-12
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (ll i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define invrep(i,b,a) for(int i = b; i >= a; --i)

vector <bool> crib;
void criba(ll b)
{
    crib.assign(b, 1);
    crib[0] = 0;
    crib[1] = 0;
    repx(k, 2, sqrt(b+1) + 1)
        if(crib[k])
            for(int j=2; (j * k) < b + 1; j++)
                crib[k*j] = 0;
}
vl primes, memo[3][100001];
vl dp(ll turn, ll num) {

  //cout << turn << " " << num << "\n";
  if(num == 1 || crib[num]){
    vl aux = {(ll)INF, (ll)INF, (ll)INF};
    if(num != 1)
      aux[turn] = 1;

    //cout << "return " << aux[0] << " " << aux[1] << " " << aux[2] << "\n";
    return aux;
  }
  if(memo[turn][num][0] != -1) return memo[turn][num];

  vl ans = dp((turn + 1) % 3, num + 1);
  ans[turn] = min(ans[turn], num + 1);
  vl res;
  ll mini = ans[turn];

  //cout << "return res " << res[0] << " " << res[1] << " " << res[2] << "\n";	



  for(auto it : primes){
    if(it > num) break;
    if(num % it != 0) continue;
    res = dp((turn + 1) % 3, num / it);
    res[turn] = min(res[turn], num / it);
    if(res[turn] <= mini) {
      mini = res[turn];
      ans = res;
    }
  }

  //cout << "return2 " << ans[0] << " " << ans[1] << " " << ans[2] << "\n";

  return memo[turn][num] = ans;
}

int main(){

  ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	srand((unsigned int) time(0));

  criba(100001);
  repx(i, 1, 100000) {
    if(crib[i]) primes.pb(i);
  }

  rep(i, 3) rep(j, 100001) memo[i][j] = {-1, -1, -1};
  
  ll n;
  cin >> n;

  vl ans = {0, 0, 0};
  while(n--){
    ll x; char ch;
    cin >> ch >> x;
    vl res;
    if(ch == 'O') res = dp(0, x);
    else if(ch == 'E') res = dp(1, x);
    else res = dp(2, x);
    //cout << res[0] << " " << res[1] << " " << res[2] << "\n";
    rep(i, 3) ans[i] += min(res[i], x);
  }

  cout << ans[0] << " " << ans[1] << " " << ans[2] << "\n";

	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}