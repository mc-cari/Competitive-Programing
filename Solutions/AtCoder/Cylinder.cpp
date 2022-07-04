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

//https://atcoder.jp/contests/abc247/tasks/abc247_d?lang=en

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
    
    ll Q;
    cin >> Q;
    deque<pll> s;
    ll ac = 0, sum = 0;
    while(Q--)
    {
        ll op, x;
        cin >> op;
        
        if(op == 1)
        {
            ll c;
            cin >> x >> c;
            ac += x*c;
            s.push_back({x, c});
           
        }
        else{
            ll c;
            cin >> c;
            ll acc = 0;
             
            while(c && s.front().second <= c)
            {
                auto a = s.front(); s.pop_front();
                acc += a.first*a.second;
                c -= a.second;
            }
             
            if(!s.empty())
            {
                auto a = s.front(); s.pop_front();
                s.push_front({a.first, a.second - c});
                acc += a.first*c;
            }
            cout <<acc << "\n";
            
            
            
            
            
            

        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}