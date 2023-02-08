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

//https://codeforces.com/group/j1UosVRZar/contest/287404/problem/B

vl suma(vl& v1, vl& v2)
{
    vl v3(max(v1.size(), v2.size()), 0);

    if(v1.size() < v2.size()) swap(v1,v2);

    for(int i = 0; i < v2.size(); i++)
        v3[i] += v2[i];
    for(int i = 0; i < v1.size(); i++)
        v3[i] += v1[i];

    return v3;
}

vl mult(vl& v1, vl& v2)
{
    vl v(v1.size() + v2.size() - 1, 0);
    for(int i = 0; i < v1.size(); i++)
    {
        for(int j = 0; j < v2.size(); j++)
        {
            v[i+j] += v1[i] * v2[j];
        }
    }
    return v;
}
ll max_dig;
string s;
vl insum(ll in1, ll fin)
{
    vl pol_aux;
    vl aux;
    for(int i = in1; i <= fin; i++){
        if(s[i] == '*')
        {
            reverse(ALL(aux));

            if(pol_aux.empty())
                pol_aux = aux;
            else
            {
                pol_aux = mult(pol_aux, aux);
            }
            aux.clear();
        }
        else
        {
            max_dig = max(max_dig, (ll)s[i] - '0');
            aux.push_back(s[i] - '0');
        }
    }
    reverse(ALL(aux));
    if(pol_aux.empty())
        pol_aux = aux;
    else
        pol_aux = mult(pol_aux, aux);
    return pol_aux;
}

vl factor(ll x)
{
    vl aux;
    for(ll i = 1; i*i <= x; i++)
    {
        if(x%i == 0)
        {
            if(i*i != x) aux.push_back(x / i);
            aux.push_back(i);

        }
    }
    return aux;
}
ll eval(vl& pol, ll x, ll mod)
{
    ll res = pol[0], po = x;
    for(int i = 1; i < pol.size(); i++)
    {

        res += pol[i] * po;
        res %= mod;
        po *= x;
        po %= mod;
    
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    

    
    while(cin >> s && s.size() > 1){

        max_dig = 0;
        vl pol, pol2, aux;
        bool op = 0;
        ll prev = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '+' || s[i] == '=')
            {
                aux = insum(prev, i-1);
                if(!op && pol.empty())
                    pol = aux;
                else if(op && pol2.empty())
                    pol2 = aux;
                else
                {

                    if(!op)
                        pol = suma(pol, aux);
                    else 
                        pol2 = suma(pol2, aux);
                }
                if(s[i] == '=')
                    op = 1;
                prev = i+1;
                
            }
        }
        aux = insum(prev, s.size()-1);
        if(pol2.empty())
            pol2 = aux;
        else
            pol2 = suma(pol2, aux);

        for(int i = 0; i < pol2.size(); i++)
        {
            pol2[i] = -pol2[i];
        }
        pol = suma(pol, pol2);

        

        bool ceros = 1;

        for(int i = 0; i < pol.size(); i++)

            if(pol[i])ceros = 0;


        if(ceros)
        {
            cout << max(max_dig + 1, (ll)2) << "+\n";
            continue;
        }
        reverse(ALL(pol));
        while(pol.back() == 0)
            pol.pop_back();
        reverse(ALL(pol));

        set<ll> poss;
        vl ans;

        vl facs1 = factor(abs(pol[0])), facs2 = factor(abs(pol.back()));
        
        for(int i = 0; i < facs1.size(); i++)
        {
            for(int j = 0; j < facs2.size(); j++)
            {
                
                if(facs1[i] < facs2[j])continue;
                poss.insert(facs1[i] / facs2[j]);
                
            }
        }
        for(auto it : poss)
        {
            if(eval(pol, it, 1e9 + 9) == 0 && eval(pol, it, 1e9 + 7) == 0 && it > max(max_dig, 2LL))
            {
                ans.push_back(it);
            }
        }
        sort(ALL(ans));
        if(ans.empty())
            cout << "*\n";

        else
        {
            ll id = 0;
            for(auto it  : ans)
            {
                if(id) cout << " ";
                cout << it;
                id++;
            }cout<<"\n";
        }
    }
    
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
