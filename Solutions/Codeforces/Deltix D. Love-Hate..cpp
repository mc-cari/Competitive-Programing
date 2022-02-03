#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long long db;
#define INF 1e9
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    

    ll n, m, p;

    cin >> n >> m >> p;
    vl bits(n, 0);
    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for(ll j = 0; j < m; j++)
        {
            if(s[j] == '1') bits[i] |= (1LL << j);
        }

    }
    ll maxi = 0, ans = 0, half = n/2;
    if(n%2 == 1)half++;
    vl prob;
    for(int i = 0; i < n; i++)
    {
        prob.push_back(i);
    }
    random_shuffle(ALL(prob));

    
    for(int _ = 0; _ < min((int)prob.size(), 120); _++)
    {
        ll in = prob[_];


        vl masks((1 << 16), 0);
        vl m_b(61, 0), b_m(16, 0);
    
        ll cont = 0;
        for(ll i = 0; i < m; i++)
        {
            if((1LL << i) & bits[in])
            {
                m_b[i] = cont;
                b_m[cont] = i;
                cont++;
            } 
        }

        
        for(int i = 0; i < n; i++)
        {
            if(i == in) continue;
            ll x = bits[i] & bits[in];
            //cout<<" "<<x<<"\n";
            ll m_aux = 0;
            for(ll j = 0; j < m; j++)
            {
                if((1LL << j) & x)
                {
                    m_aux |= (1LL << m_b[j]);
                } 
            }

            masks[m_aux]++;
        }

        //propagate val in mask to all its submask
        for (int i = 0; i < p; i++)
        {
            for(int z = 0; z < (1 << p); z++)
            {
                if((z & (1 << i)) == 0)
                    masks[z] += masks[z | (1 << i)];
            }
        }
        for(int z = 0; z < (1 << p); z++)
        {
            cont = 0;
            ll aux = 0;
            for(int i = 0; i < p; i++)
            {
                if((z & (1 << i))){
                    cont++;
                    aux |= (1LL << b_m[i]);
                }
            }
            if(cont > maxi && masks[z]+1 >= half)
            {
                
                maxi = cont;
                ans = aux;

            }
            
        }
    }
    for(int i = 0; i < m; i++)
    {
        if((1LL << i) & ans) cout << "1";
        else cout << "0";
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
