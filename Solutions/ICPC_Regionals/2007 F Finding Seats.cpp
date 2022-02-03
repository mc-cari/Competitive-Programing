#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

// https://www.urionlinejudge.com.br/judge/es/problems/view/1365

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll R, C, K;
    while(cin >> R >> C >> K)
    {
      if(R + C + K == 0)break;
      char M[R][C];
      ll S[R+1][C+1];
      ll ans = INF;
      memset(S, 0, sizeof(S));
      ll sum = 0;
      for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
        {
          cin>>M[i][j];
          if(M[i][j] == '.')S[i+1][j+1] = 1;
          S[i+1][j+1] += S[i][j+1] + S[i+1][j] - S[i][j];
        }
      for(int i = 0; i < R; i++)for(int j = i; j < R; j++)
      {
        ll postz = 0;
        for(int z = 0; z < C; z++)
        {
          while(postz != C-1 && K > S[j+1][postz+1] - S[i][postz+1] - S[j+1][z] + S[i][z])
          {
            postz++;
          }
          if(S[j+1][postz+1] - S[i][postz+1] - S[j+1][z] + S[i][z] >= K)
          {
            ans = min((j-i+1)*(postz-z+1),ans);
          }
        }
      }
      cout<<ans<<"\n";

    }
    return 0;
}
