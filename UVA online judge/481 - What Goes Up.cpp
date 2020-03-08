#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=422
vl A,p;
void print_LIS(int i) {                          // backtracking routine
  if (p[i] == -1) { cout<<A[i]<<"\n"; return; }// base case
  print_LIS(p[i]);                               // backtrack
  cout<<A[i]<<"\n";
}
int main()
{
    ll n;
    int x;
    while(cin>>x)
    {
        A.push_back(x);
    }
    n=A.size();
    int k = 0, lis_end = 0,last_k=0;
    vl L(n, 0), L_id(n, 0);
    p.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
        L[pos] = A[i];
        L_id[pos] = i;
        p[i] = pos ? L_id[pos-1] : -1;
        if (pos == k) {

          k = pos+1;
          lis_end = i;
        }
        else if(pos == k-1)
        {
            lis_end = i;
        }
    }
    cout<<k<<"\n-\n";
    print_LIS(lis_end);


    return 0;
}
