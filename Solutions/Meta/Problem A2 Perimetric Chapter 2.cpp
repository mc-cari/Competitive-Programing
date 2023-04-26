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

//https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/A2

ll M = 1000000007;
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t;
    cin >> t;
    for(int T = 1; T <= t; T++)
    {
        ll n, k, x, A, B, C, D;
        cin >> n >> k;
        vl L, W, H;
        for(int i = 0; i < k; i++)
        {
            cin >> x;
            L.push_back(x);
        }
        cin >> A >> B >> C >> D;
        for(int i = k; i < n; i++)
        {
            L.push_back((A * L[i-2] + B * L[i-1]+ C) % D + 1);
        }

        for(int i = 0; i < k; i++)
        {
            cin >> x;
            W.push_back(x);
        }
        cin >> A >> B >> C >> D;
        for(int i = k; i < n; i++)
        {
            W.push_back((A * W[i-2] + B * W[i-1]+ C) % D + 1);
        }

        for(int i = 0; i < k; i++)
        {
            cin >> x;
            H.push_back(x);
        }
        cin >> A >> B >> C >> D;
        for(int i = k; i < n; i++)
        {
            H.push_back((A * H[i-2] + B * H[i-1]+ C) % D + 1);
        }
        
        set<tuple<ll, ll, ll >> q;
        ll ans = 1, P = 0;
        for(int i = 0; i < n; i++)
        {
            
            pll h = {L[i], L[i] + W[i]};
            auto itl = q.lower_bound(make_tuple(L[i], -1, -1));
            auto itr = itl, itauxl = itl;
            ll cont = 0, pre = L[i], left = 0, right = L[i] + W[i];
            if(itl != q.begin() && get<1>(*prev(itl)) >= L[i])
            {
                itauxl = prev(itl);
                pre = get<1>(*prev(itl));
                cont++;
                right = max(right, get<1>(*itauxl));
                P -= 2*H[i];
                left = L[i] - get<0>(*prev(itl));
            }
            for(auto it = itl; it != q.end(); it++)
            {
                
                if(get<0>(*it) > L[i] + W[i])
                {
                    break;
                } 
                itr++;
                right = max(right, get<1>(*it));
                P += 2*max(0LL, get<0>(*it) - pre);
                P -= 2*H[i];
                pre = get<1>(*it);
                cont++;
            }
            
            right = right - (L[i] + W[i]);
            if(cont == 0)
            {
                P += 2*W[i] + 2*H[i];
                q.insert(make_tuple(L[i], L[i] + W[i], H[i]));
            }
            else
            {
                P += 2*max(0LL, L[i] + W[i] - pre);
                P += 2*H[i];
                q.erase(itauxl, itr);
                q.insert(make_tuple(L[i] - left, L[i] + W[i] + right, 5));
            }
            //cout<<P<<" "<<L[i]<<" "<<W[i]<<" "<<H[i]<<" "<<cont<<"\n";
            while(P < 0)P += M;
            P %= M;
            ans *= P;
            ans %= M;
        }
        cout<<"Case #"<<T<<": "<<ans<<"\n";
    }



    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
