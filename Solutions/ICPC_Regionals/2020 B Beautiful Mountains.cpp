#include<bits/stdc++.h>
 
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
 
 
//https://codeforces.com/gym/103185/problem/B
 
int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    
    ll n, x, prev = -1;
    cin >> n;
    vl c, L(n, -1), R(n, n+1);
    stack<ll > l, r;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x);

        if(!r.empty() && prev != -1 && x != -1 &&  x < prev)
        {
            vl aux;
            while(!r.empty() && c[r.top()] == -1)
            {
                aux.push_back(r.top());
                r.pop();
            }
            while (!r.empty())
            {
                R[r.top()] = i;
                r.pop();
            }
            for(auto it : aux)r.push(it);
            prev = -1;
            
        }
        if(x != -1)prev = x;
        r.push(i);
    }
    prev = -1;
    while(!r.empty())r.pop();
    for(int i = n-1; i >= 0; i--)
    {

        if(!r.empty() && prev != -1 && c[i] != -1 &&  c[i] < prev)
        {
            vl aux;
            while(!r.empty() && c[r.top()] == -1)
            {
                aux.push_back(r.top());
                r.pop();
            }
            while (!r.empty())
            {
                L[r.top()] = i;
                r.pop();
            }
            for(auto it : aux)r.push(it);
            prev = -1;
            
        }
        if(c[i] != -1)prev = c[i];
        r.push(i);
    }

    bool o = 0;
    for(int k = 3; k <= n; k++)
    {
        bool o2 = 1;
        for(int i = 0; i < n; i+= k)
        {
            ll left, right;
            if(i+k-1 >= n)
            {

                right = min(n-1, R[i]);
                left = max((ll)i, L[n-1]);
                if(n - i < 3 ) o2 = 0;
            }
            else
            {
                right = min(n-1, R[i]);
                left = max((ll)i, L[i+k-1]);
            }
            if(right - 2 < left) o2 = 0;

        }
        if(o2)o = 1;
    }
    if(o) cout << "Y\n";
    else cout << "N\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
