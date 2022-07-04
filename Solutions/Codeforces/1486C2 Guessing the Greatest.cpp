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



int main(){


   ll n;
   cin >> n;

   cout << flush << "? "<<1 << " " << n << "\n";
   ll pos;
   cin >> pos;
    ll q;
    ll dir = -1;
    if(pos == 1)
    {
        dir = 1; // r
    }
    else if(pos == n) dir = 2;
    else{
        cout << flush << "? "<<1 << " " << pos << "\n";
        cin >> q;
        if(q == pos) dir = 2;
        else dir = 1;
    }
    

   

    if(dir == 1)
    {
        ll l = pos, r = n-1, p, res = -1;
        while(l <= r)
        {
            p = (l + r) / 2;
            cout << flush << "? "<<pos << " " << p+1 << "\n";
            cin >> q;
            if(q != pos)l = p+1;
            else 
            {
                r = p-1;
                res = p;
            }
        }
        cout << flush <<"! " << res+1 << "\n";
    }
    else
    {
        ll l = 0, r = pos-2, p, res = -1;
        while(l <= r)
        {
            p = (l + r) / 2;
            cout << flush << "? "<<p+1 << " " << pos << "\n";
            cin >> q;
            if(q != pos)r = p-1;
            else 
            {
                l = p+1;
                res = p;
            }
        }
        cout << flush <<"! "<< res+1 << "\n";
    }
    


    
    return 0;
}