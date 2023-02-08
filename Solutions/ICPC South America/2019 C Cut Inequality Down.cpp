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

//https://matcomgrader.com/problem/9636/cut-inequality-down/

vl acum;
ll N, L, U;
struct SparseTable
{
    vector<vl >SP;
    SparseTable(vl&A)
    {
        ll n=A.size();
        SP.push_back(A);
        ll maxlog = 63 - __builtin_clzll(n);
        for(ll i=1;i<=maxlog;i++)
        {
            vl c;
            for(ll j=0;j<n-(1<<i)+1;j++)
            {
                c.push_back(max(SP[i-1][j],SP[i-1][j+(1LL<<(i-1))]));
            }
            SP.push_back(c);
        }
    }
    ll op(ll l,ll r)
    {
        ll maxlog = 63 - __builtin_clzll(r-l+1);
        return max(SP[maxlog][l],SP[maxlog][r-(1LL<<maxlog)+1]);
    }
};
struct SparseTablemin
{
    vector<vl >SP;
    SparseTablemin(vl& A)
    {
        ll n=A.size();
        SP.push_back(A);
        ll maxlog = 63 - __builtin_clzll(n);
        for(ll i=1;i<=maxlog;i++)
        {
            vl c;
            for(ll j=0;j<n-(1<<i)+1;j++)
            {
                c.push_back(min(SP[i-1][j],SP[i-1][j+(1LL<<(i-1))]));
            }
            SP.push_back(c);
        }
    }
    ll op(ll l,ll r)
    {
        ll maxlog = 63 - __builtin_clzll(r-l+1);
        return min(SP[maxlog][l],SP[maxlog][r-(1LL<<maxlog)+1]);
    }
};
struct SparseTableLCA
{
    ll maxlg;
    vector<vector<pll> >SPup, SPlow;
    SparseTableLCA(vector<pll>& nextU, vector<pll>& nextL)
    {
        ll n=nextU.size();
        SPup.push_back(nextU);
        SPlow.push_back(nextL);
        maxlg= 63 - __builtin_clzll(n);
        for(ll i=1;i<= maxlg;i++)
        {
            vector<pll> c;
            for(ll j=0;j < n;j++)
            {

                if(SPup[i-1][j].second == -1)
                {
                    c.push_back(SPup[i-1][j]);
                }
                else if(SPup[i-1][j].second == 0)
                {
                    c.push_back(SPlow[i-1][SPup[i-1][j].first]);
                }
                else
                {
                    c.push_back(SPup[i-1][SPup[i-1][j].first]);
                }
                
            }
            SPup.push_back(c);
            c.clear();
            for(ll j=0;j < n;j++)
            {
                
                if(SPlow[i-1][j].second == -1)
                {
                    c.push_back(SPlow[i-1][j]);
                }
                else if(SPlow[i-1][j].second == 0)
                {
                    c.push_back(SPlow[i-1][SPlow[i-1][j].first]);
                }
                else
                {
                    c.push_back(SPup[i-1][SPlow[i-1][j].first]);
                }
            }
            SPlow.push_back(c);
        }
    }
    pll query(ll in, ll R,ll up)
    {
        for(ll i = maxlg; i >= 0; i--)
        {
            if(up == 1 && SPup[i][in].first <= R)
            {
                up = SPup[i][in].second;
                in = SPup[i][in].first;
                
            }
            else if(up == 0 && SPlow[i][in].first <= R)
            {
                up = SPlow[i][in].second;
                in = SPlow[i][in].first;
            }
        }
        return {in, up};
    }
};

pll quer(ll in, ll c, SparseTable& SP, SparseTablemin& SPmin)
{

  ll up = 1;

  ll l = in+1, r = N-1, p, res1 = INF;
  while(l<=r)
  {
      p=(l+r)/2;
      ll aux = 0;
      if(in >= 0) aux = acum[in];
      if(SP.op(in+1, p) - aux + c > U)
      {
        res1 = p;
        r=p-1;
      }
      else l=p+1;
  }
  ll res2 = INF; l = in+1; r = N-1;
  while(l<=r)
  {
      p=(l+r)/2;
      ll aux = 0;
      if(in >= 0) aux = acum[in];
      if(SPmin.op(in+1, p) - aux + c < L)
      {
        res2 = p;
        r=p-1;
      }
      else l=p+1;
  }
 
  if(res1 == INF && res2 == INF)up = -1;
  else if(res1 < res2)up = 1;
  else up = 0;
  if(up) return {res1, up};
  else return {res2, up};
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    ll x;
    vl A;
    vector<pll> nextU, nextL;
    cin >> N >> L >> U;
    for(ll i = 0; i < N; i++)
    {
      cin >> x;
      A.push_back(x);
      acum.push_back(x);
      if(i > 0)acum.back() += acum[i-1];
    }
    SparseTable SP(acum);
    SparseTablemin SPmin(acum);
    
    pll h;
    for(ll i = 0; i < N; i++)
    {
      h = quer(i, U, SP, SPmin);
      nextU.push_back(h);
      h = quer(i, L, SP, SPmin);
      nextL.push_back(h);
    }
    SparseTableLCA SPL(nextU, nextL);

    ll q;
    cin >> q;
    while(q--){
      ll B, E, X, ans = 0;
      cin >> B >> E >> X;
      B--; E--;
      h = quer(B-1, X, SP, SPmin);
      if(h.first >= E)
      {
        ll aux = 0;
        if(B > 0)aux = acum[B-1];
        cout<<min(U, max(L, acum[E] - aux + X))<<"\n";
      }
      else
      {
        h = SPL.query(h.first, E, h.second);
        
        ll aux = acum[h.first];
        ll aux2 = 0;
        if(h.second == 1)aux2 = U;
        else aux2 = L;
        cout<<min(U, max(L, acum[E] - aux + aux2))<<"\n";
      }
      
    }


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
