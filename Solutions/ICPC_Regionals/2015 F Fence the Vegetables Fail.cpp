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

//https://www.urionlinejudge.com.br/judge/es/problems/view/2007

struct point { ll x, y;
    point() { x = y = 0.0; }                      
    point(ll _x, ll _y) : x(_x), y(_y) {}        

  };
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll P, V, x, y;
    while(cin >> P >> V  && (P + V)){

        vector<tuple<ll, ll, ll, ll> > q;
        ll value = 1;
        for(int i = 0; i < P; i++)
        {
            cin >> x >> y;
            q.push_back(make_tuple(x, 0, y, value));
            value++;
        }
        point p;
        vector<point> Q;
        
        
        for(int i = 0; i < V; i++)
        {
            cin >> p.x >> p.y;
            Q.push_back(p);

        }
        
        for(int i = 0; i < V; i++)
        {
            if(Q[i].x == Q[(i+1)%V].x)
            {
                if(Q[i].x > Q[(i-1+V)%V].x && Q[(i+1)%V].x > Q[(i+2)%V].x)
                {
                    
                    q.push_back(make_tuple(Q[i].x, 1, min(Q[i].y, Q[(i+1)%V].y), max(Q[i].y, Q[(i+1)%V].y)));
                }
                else if(Q[i].x < Q[(i-1+V)%V].x && Q[(i+1)%V].x < Q[(i+2)%V].x)
                {
                    q.push_back(make_tuple(Q[i].x, 2, min(Q[i].y, Q[(i+1)%V].y), max(Q[i].y, Q[(i+1)%V].y)));
                }
                else
                {
                    
                    q.push_back(make_tuple(Q[i].x, 3, min(Q[i].y, Q[(i+1)%V].y), max(Q[i].y, Q[(i+1)%V].y)));
                }
                
            }
        }
        sort(ALL(q));
        set<pll> segs;
        ll ans = 0;
        for(auto it : q)
        {
            ll tipe;
            if(get<1>(it) == 0)
            {
                tie(x, tipe, y, value) = it; 
                auto it2 = segs.upper_bound({y+1, -INF});
                if(it2 == segs.begin() || (*prev(it2)).second < y)
                    ans += value;
            }
            else
            {
                ll a, b;
                tie(x, tipe, a, b) = it;
                if(tipe == 2)
                {
                    auto it2 = segs.upper_bound({a+1, -INF});
                    if(it2 != segs.begin() && (*prev(it2)).first < a && (*prev(it2)).second > b)
                    {
                        ll aux1 = (*prev(it2)).first;
                        ll aux2 = (*prev(it2)).second;
                        segs.erase(prev(it2));
                        segs.insert({b, aux2});
                        segs.insert({aux1, a});
                    }
                    else
                    {
                        segs.insert({a, b});
                    }

                }
                else if(tipe == 1)
                {
                    
                    auto it2 = segs.find({a, b});
                    if(it2 != segs.end())
                    {
                        segs.erase(it2);
                    }
                    else
                    {
                        auto it2 = segs.upper_bound({b, -INF});

                            auto it3 = prev(it2);
                            pll p1 = {(*it2).first, (*it2).second}, p2 = {(*it3).first, (*it3).second}; 
                            ll B = (*it2).second;
                            ll A = (*it3).first;
                            segs.erase(p1);
                            segs.erase(p2);
                            segs.insert({A, B});

                    }
                }
                else
                {
                    auto it2 = segs.upper_bound({a, -INF});
                    auto it3 = segs.upper_bound({b, -INF});
                    auto it4 = segs.upper_bound({a+1, -INF});
                    auto it5 = segs.upper_bound({b+1, -INF});
                    // cuatro casos posibles
                    
                    if(it2 != segs.end() && (*it2).first == a)
                    {
                        ll aux = (*it2).second;
                        segs.erase(it2);
                        segs.insert({b, aux});
                    }
                    else if(it3 != segs.end() && (*it3).first == b)
                    {
                        ll aux = (*it3).second;
                        segs.erase(it3);
                        segs.insert({a, aux});
                    }
                    else if(it4 != segs.begin() && (*prev(it4)).second == a )
                    {
                        ll aux = (*prev(it4)).first;
                        segs.erase(prev(it4));
                        segs.insert({aux, b});
                    }
                    else
                    {
                        ll aux = (*prev(it5)).first;
                        segs.erase(prev(it5));
                        segs.insert({aux, a});
                    }
                    
                }
                
            }

        }
        cout<<ans<<"\n";

    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
