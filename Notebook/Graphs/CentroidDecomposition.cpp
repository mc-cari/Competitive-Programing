#include "../Header.cpp"

// all tree diameters pass through the centroid

//https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/master/graphs/centroid.cpp
const int MAXN = 1e5 + 5;
vector<int> g[MAXN];int n;
bool tk[MAXN];
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	return szt[x];
}
void cdfs(int x=0, int f=-1, int sz=-1){ // O(nlogn)
	if(sz<0)sz=calcsz(x,-1);
	for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sz){
		szt[x]=0;cdfs(y,f,sz);return;
	}
	tk[x]=true;fat[x]=f;
	for(auto y:g[x])if(!tk[y])cdfs(y,x);
}
void centroid(){memset(tk,false,sizeof(tk));cdfs();}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  ll t;
  cin >> t;
  for(int T = 1; T <= t; T++) {
    
    memset(memo, -1, sizeof(memo));
    ll x;
    cin >> N >> K;
    B.clear();
    ac.clear();
    ac.push_back(0);
    for(int i = 0; i < N; i++)
    {
      cin >> x;
      B.push_back(x);
      ac.push_back(x);
      ac[i+1] += ac[i];
    }
    ll acum = 0;
    for(int i = 0; i < N; i++)
    {
        acum += B[i];
        if(acum == ac[i+1])cout<<"1\n";
        else cout <<"0\n";
    }

    ll ans = INF;
    for(int i = 0; i < N; i++)
    {
      ans = min(ans, dp(i, 0, 0));
    }
    if(ans >= INF) ans = -1;
    cout << "Case #" << T << ": ";
    cout << ans << "\n";
  }
}