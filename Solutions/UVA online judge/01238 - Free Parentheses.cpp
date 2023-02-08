#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef long double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3679
vl c;
vl sgn;
set<ll>sums;
ll memo[32][6100][32];
void solver(ll pos, ll suma, ll acum)
{
    if(pos == c.size())
    {
      sums.insert(suma);
      return;
    }
    if(memo[pos][suma + 3000][acum] != -1)
      return;

    memo[pos][suma + 3000][acum] = 1;
    
    ll sign = 1;
    if (acum % 2 == 1)sign = -1;
    solver(pos + 1, suma + c[pos] * sign, acum);

    if (sgn[pos] < 0)
    {
      solver(pos + 1, suma + c[pos] * sign, acum + 1);
    }
    else if(acum)
    {
      solver(pos + 1, suma + c[pos] * sign, acum - 1);
    }
    return;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    while(getline(cin, s))
    {
      ll sign = 1;
      c.clear();
      sgn.clear();
      ll prev = 0;
      string sr = "";
      for(int i = 0; i < s.size(); i++)
      {
        if(s[i] != ' ')
        {
          sr += s[i];
        }
        else
        {
          if (sr == "-")sign = -1;
          else if (sr == "+")sign = 1;
          else if (sr != "")
          {
            c.push_back(stoll(sr) * sign);
            sgn.push_back(sign);
          }
          sr = "";
        
        }
      }
      if (sr == "-")sign = -1;
      else if (sr == "+")sign = 1;
      else if (sr != "")
      {
        c.push_back(stoll(sr) * sign);
        sgn.push_back(sign);
      }
      sums.clear();
      memset(memo, -1, sizeof(memo));
      solver(0, 0, 0);
      cout<<sums.size()<<"\n";
    }
    
    return 0;
}
