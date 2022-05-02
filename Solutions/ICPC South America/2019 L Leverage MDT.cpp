#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://matcomgrader.com/problem/9640/leverage-mdt/


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    ll n, m;
    cin >> n >> m;
    string s;
    vector<string> c;
    vector<vl> sums(2*n, vl(2*m, 0));
    for(int i = 0; i < n; i++)
    {
      cin >> s;
      c.push_back(s);
    }
    for(int i = 0; i < 2*n-1; i++)
    {
      for(int j = 0; j < 2*m-1; j++)
      {
        if(j%2 == 1 && i%2 != 1 && c[i/2][(j-1)/2] != c[i/2][(j+1)/2])sums[i][j]++;
        if(i > 0)sums[i][j] += sums[i-1][j];
        if(j > 0)sums[i][j] += sums[i][j-1];
        if(i > 0 && j > 0)sums[i][j] -= sums[i-1][j-1];
      }
    }
    ll res = 0;
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < m; j++)
      {


        ll l=0,r=min(n - i - 1, m - j - 1),p, ans = 0;
        while(l<=r)
        {
            p=(l+r)/2;
            ll sum = sums[2*i + 2*p][2*j + 2*p];
            if(i > 0)sum -= sums[2*i-1][2*j + 2*p];
            if(j > 0)sum -= sums[2*i + 2*p][2*j-1];
            if(i > 0 && j > 0)sum += sums[2*i-1][2*j-1];
            if(sum == 0)
            {
              l=p+1;
              ans = p;
            }
            else r=p-1;
        }
        res = max(res, ans+1);
      }
    }
    cout<<res*res<<"\n";


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
