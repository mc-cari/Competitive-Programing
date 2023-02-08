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

//https://codeforces.com/contest/13/problem/E

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, x;
    vl p;
    cin >> n >> m;
    ll k = sqrt(n);
    vl pow(n, 0), cont(n, 0), nex(n, 0);
    for(int i = 0; i < n; i++)
    {
      cin >> x;
      pow[i] = i / k;
      p.push_back(x);
    }

    for(int i = n - 1; i >= 0; i--)
    {
      if(i + p[i] >= n) 
      {
        nex[i] = n + i;
        cont[i] = 1;
      }
      else if(pow[i] != pow[i + p[i]])
      {
        nex[i] = i + p[i];
        cont[i] = 1;
      }
      else
      {
        nex[i] = nex[i + p[i]];
        cont[i] = 1 + cont[i + p[i]];
      }

    }
    
    while(m--)
    {
      ll a, b;
      cin >> x;
      if(x)
      {
        cin >> a;
        ll count = 0, fin = a - 1;
        while(nex[fin] < n)
        {
          count += cont[fin];
          fin = nex[fin];
        }
        count += cont[fin];
        fin = nex[fin] - n;
        cout << fin + 1 << " " << count << "\n";
      }
      else
      {
        cin >> a >> b;
        p[a-1] = b;
        ll P = pow[a-1], in = a-1;
        while(in >= 0 && pow[in] == P)
        {
          if(in + p[in] >= n) 
          {
            nex[in] = n + in;
            cont[in] = 1;
          }
          else if(pow[in] != pow[in + p[in]])
          {
            nex[in] = in + p[in];
            cont[in] = 1;
          }
          else
          {
            nex[in] = nex[in + p[in]];
            cont[in] = 1 + cont[in + p[in]];
          }
          in--;
        }

      }
    }
    


    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
    
}