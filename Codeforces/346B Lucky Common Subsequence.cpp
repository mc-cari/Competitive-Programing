#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/problemset/problem/346/B

string s1, s2, vir;

#define rep(i,a,b) for(int i=a; i<b; ++i)
int lps[102];
// Build longest proper prefix/suffix array (lps) for pattern
// lps[i] = length of the longest proper prefix which is also suffix in pattern[0 .. i]
void init_lps(string& pattern) {
    int n = pattern.size();
    lps[0] = 0; // base case: no proper prefix/suffix for pattern[0 .. 0] (length 1)
    rep(j, 1, n) { // for each pattern[0 .. j]
        int i = lps[j-1]; // i points to the char next to lps of previous iteration
        while (pattern[i] != pattern[j] and i > 0) i = lps[i-1];
        lps[j] = pattern[i] == pattern[j] ? i+1 : 0;
    }
}

ll memo[101][101][101];
ll dp(ll x, ll y, ll k )
{
   if (x == s1.size() || y == s2.size())
     return memo[x][y][k] = 0;
   if(memo[x][y][k] != -1)return memo[x][y][k];
   ll ans = 0;
   if (s1[x] == s2[y])
   {
     ll auxk = k;
     while (vir[auxk] != s1[x] and auxk > 0) auxk = lps[auxk-1];

     if(vir[auxk] == s1[x]){
         auxk++;
        if(auxk != vir.size() )
          ans = 1 + dp(x+1, y+1, auxk);
        else ans = max(dp(x+1, y, k), dp(x, y+1, k));
     }
     else ans = 1 + dp(x+1, y+1, auxk);
   }
     
    ans = max(ans, max(dp(x+1, y, k), dp(x, y+1, k)));
    return memo[x][y][k] = ans;
}

void dp2( ll x, ll y, ll k )
{
   if (x == s1.size() || y == s2.size())
     return;

   ll min1, min2 = 0;

    min1 = max(dp(x+1, y, k), dp(x, y+1, k));

    if (s1[x] == s2[y])
    {
      ll auxk = k;
      while (vir[auxk] != s1[x] and auxk > 0) auxk = lps[auxk-1];

      if(vir[auxk] == s1[x]){
          auxk++;
          if(auxk != vir.size() )
            min2 = 1 + dp(x+1, y+1, auxk);
          else min2 = max(dp(x+1, y, k), dp(x, y+1, k));
      }
      else min2 = 1 + dp(x+1, y+1, auxk);
    }
   
   if (s1[x] == s2[y] && min2 > min1)
   {
     ll auxk = k;
     while (vir[auxk] != s1[x] and auxk > 0) auxk = lps[auxk-1];

     if(vir[auxk] == s1[x] ){
       auxk++;
      if(auxk != vir.size()){
        
          cout<<s1[x];
          dp2(x+1, y+1, auxk);
      }
      else 
      {
        if(dp(x+1, y, k) > dp(x, y+1, k))
        dp2(x+1, y, k);
        else dp2(x, y+1, k);
      }
     }
     else 
     {
        cout<<s1[x];
        dp2(x+1, y+1, auxk);
      }
     return;
   }

   if(dp(x+1, y, k) > dp(x, y+1, k))
       dp2(x+1, y, k);
    else dp2(x, y+1, k);
     
}

int main()
{
    memset(memo, -1, sizeof(memo));
    cin >> s1 >> s2 >> vir;
    init_lps(vir);
    if(dp(0, 0, 0) == 0)
      cout<<dp(0, 0, 0)<<"\n";
    else {
      dp2(0, 0, 0);
      cout<<"\n";
    }
      
}
