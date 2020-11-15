#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://codeforces.com/group/YjFmW2O15Q/contest/102363/attachments

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, x, y;
    cin >> n;
    char s;
    vector< tuple<ll,ll,ll,ll> > q;
    vl ori(n, 0);
    for(int i = 0; i < n; i++)
    {
        cin >> s >> x >> y;
        if(s == 'D')
        {
            q.push_back(make_tuple(x, 0, 0, i));
            q.push_back(make_tuple(y, 1, 0, i));
        }
        else
        {
            q.push_back(make_tuple(x, 0, 1, i));
            q.push_back(make_tuple(y, 1, 1, i));
        }
        ori[i] = x;
        
    }

    ll ans = 0;
    sort(ALL(q));
    multiset<ll> Ds, Js;
    for(auto it : q)
    {
        ll v, tipe, dir, id;
        tie(v, dir, tipe, id) = it;

        if(dir == 0)
        {
            if(tipe == 0)
            {
                Ds.insert(v);
            }
            else
            {
                Js.insert(v);
            }
            
        }
        else
        {
            if(tipe == 0)
            {
                Ds.erase(Ds.find(ori[id]));

                if(!Js.empty()){
                    ll mini = *Js.begin();
                    ans = max(ans, v - max(mini, ori[id]));
                }
            }
            else
            {
                Js.erase(Js.find(ori[id]));

                if(!Ds.empty()){
                    ll mini = *Ds.begin();
                    ans = max(ans, v - max(mini, ori[id]));
                }
            }
        }
        
    }
    cout << ans << "\n";

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
