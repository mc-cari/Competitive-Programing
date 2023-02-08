#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);


//https://codeforces.com/problemset/problem/343/C

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, x;
    cin >> n >> m;
    vl c, d;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x);
    }
    for(int i = 0; i < m; i++)
    {
        cin >> x;
        d.push_back(x);
    }
    sort(ALL(c));
    ll l=0 ,r=100000000000 ,p , res = -1;
    while(l<=r)
    {
        p=(l+r)/2;

        bool can = 1;
        ll in = 0, prev = -1;
        for(int i = 0; i < m; i++)
        {
            if(d[i] <= prev)continue;
            while(in < c.size() && c[in] + p < d[i]) in++;
            if(in == c.size())
            {
                can = 0;
                break;
            }

            if(c[in] <= d[i])prev = c[in] + p;
            else
            {
                
                ll new1 = (p - (c[in] - d[i])) / 2;
                ll new2 = p - 2*(c[in] - d[i]);
                if(c[in] - d[i] > p)
                {
                    can = 0;
                    break;
                }
                else
                {
                    prev = max(c[in] + new1, c[in] + new2);
                }
            }
            in++;
            
        }
        if(!can)l=p+1;
        else 
        {
            res = p;
            r=p-1;
        }

    }
    cout<<res<<"\n";


    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
