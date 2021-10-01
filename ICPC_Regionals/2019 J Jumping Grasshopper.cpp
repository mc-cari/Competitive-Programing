#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;


typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e15
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://matcomgrader.com/problem/9644/jumping-grasshopper/

int main(){
	ios_base::sync_with_stdio(0);

    cin.tie(0);
   
    ll n, m, x, y, maxi = 0;
    cin >> n >> m;

    vl plants;
    //direction to R .. to L
    set<pll> L, R;
    unordered_map<ll, ll>pos;

    for(int i=0; i<n; i++)
    {
        cin >> x;
        plants.push_back(x);
        pos[x] = i;
        maxi = max(maxi, x);

        if(R.empty())R.insert({i, x});
        else if((*prev(R.end())).second < x)R.insert({i, x});
    }
    for(int i = n-1; i >= 0; i--)
    {
        
        if(L.empty())L.insert({-i, plants[i]});
        else if((*prev(L.end())).second < plants[i])L.insert({-i, plants[i]});
    }
    
    while(m--)
    {
        char a;
        cin >> a;
        if(a == 'L')
        {
            cin >> x;
            if(R.count({x-1, plants[x-1]}) || plants[x-1] == maxi)
            {
                cout << x << "\n";
                continue;
            }
            
            if(x <= (*prev(R.end())).first)
            {
                auto it = R.lower_bound({x, 0});
                cout << (*it).first+1 << "\n";
            }
            else
            {
                auto it = L.lower_bound({-(x-2), 0});
                cout << -(*it).first+1 << "\n";
            }
        }
        else if(a == 'R')
        {
            cin >> x;
            if(L.count({-(x-1), plants[x-1]}) || plants[x-1] == maxi)
            {
                cout << x << "\n";
                continue;
            }
            if(x <= (*prev(R.end())).first)
            {
                auto it = R.lower_bound({x, 0});
                cout << (*it).first+1 << "\n";
            }
            else
            {
                auto it = L.lower_bound({-(x-2), 0});
                cout << -(*it).first+1 << "\n";
            }
        }
        else
        {
            cin >> x >> y;
            plants[x-1] = y;
            maxi = max(maxi, y);
            auto it = R.lower_bound({x-1, 0});
            bool aux = 0;

            if(it == R.begin() || (*prev(it)).second < y) aux = 1;

            while(it != R.end())
            {
                if((*it).second > y)break;

                it = next(it);
                R.erase(prev(it));
            }
            if(aux)
                R.insert({(x-1), y});



            aux = 0;
            auto it2 = L.lower_bound({-(x-1), 0});
            if(it2 == L.begin() || (*prev(it2)).second < y) aux = 1;
            while(it2 != L.end())
            {
                
                if((*it2).second > y)break;
                
                it2 = next(it2);
                
                L.erase(prev(it2));
            }
            if(aux)
                L.insert({-(x-1), y});
           
            
        }
    }



    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
