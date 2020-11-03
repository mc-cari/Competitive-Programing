#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://atcoder.jp/contests/arc105/tasks/arc105_c

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, m, x, l, v, maxw = 0;
    cin >> n >> m;

    vl c;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        maxw = max(maxw, x);
        c.push_back(x);
    }
    vp d;
    for(int i = 0; i < m; i++)
    {
        cin >> l>> v;
        d.push_back({v, l});
    }
    
    sort(ALL(d));
    vp ord;
    vl d2;
    ll in = 0;
    for(int i = 0; i < m; i++)
    {
        if(i != m-1 && d[i].first == d[i+1].first)continue;
        ord.push_back({d[i].first, in});
        in++;
        d2.push_back(d[i].second);
    }
    vl maxis;
    ll MAX = -1;
    for(int i = 0; i < in; i++)
    {
        MAX = max(MAX, d2[i]);
        maxis.push_back(MAX);
    }
    if(maxw > d[0].first)
    {
        cout<<"-1\n";
        return 0;
    }
    ll ans = INF;  
    sort(ALL(c));
    do {
        vp stac;
        stac.push_back({c[0], 0});
        for(int i = 1; i < n; i++)
        {

            ll maxi = stac.back().second;
            ll acum = c[i];

            for(int j = stac.size() - 1; j >= 0; j--)
            {
                acum += stac[j].first;
                ll L=0 ,r=in-1 ,p , ind = -1;
                while(L<=r)
                {
                    p=(L+r)/2;
                    if(acum > ord[p].first)
                    {
                        ind = ord[p].second;
                        L=p+1;
                    }
                    else r=p-1;
                }


                if(ind != -1)
                    maxi = max(maxi, maxis[ind] + stac[j].second);
                
            }
            if(maxi == stac.back().second)stac.back().first += c[i];
            else stac.push_back({c[i], maxi});
            

        }
        ans = min(stac.back().second, ans);
        
    } while ( next_permutation(ALL(c)) );
    cout << ans << "\n";

    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
