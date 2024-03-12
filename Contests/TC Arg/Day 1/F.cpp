#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define db double
#define rep(i, n) for(int i = 0; i<(int)n; ++i)
#define PI acos(-1.0)

db area (db a, db b, db c)
{
  db s = 0.5* (a + b + c);
  return sqrt(s) * sqrt(s - a) * sqrt(s - b) * sqrt(s - c);
}

int main()
{
  vector<ll> v(100000000, 1);

  cout << fixed << setprecision(8) << v[12] << "\n";
  return 0;
}