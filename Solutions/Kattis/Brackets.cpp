#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e10
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://open.kattis.com/problems/brackets

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    ll cont = 0, n = s.size();
    vl su, mi;
    for(int i = 0; i < n; i++)
    {
        cont = 0;
        ll mini = INF;
        for(int j = i; j < n; j++){
            if(s[j] == '(')cont++;
            else cont--;
            mini = min(mini, cont);
        }
        
        su.push_back(cont);
        mi.push_back(mini);
    }
    ll prevc = 0;
    ll prevm = INF;
    for(int i = 0; i < n; i++)
    {
        
        cont = 0;
        ll mini = INF;
        for(int j = i; j < n; j++){
            if(s[j] == ')')cont++;
            else cont--;
            mini = min(mini, cont);
            if(prevm >= 0 && mini + prevc >= 0)
            {
                if(j == n-1 && prevc + cont == 0)
                {
                    cout<<"possible\n";
                    return 0;
                }
                else if(prevc + cont + su[j+1] == 0 && cont + prevc + mi[j+1] >= 0)
                {
                    cout<<"possible\n";
                    return 0;
                }
            }
        }
        if(s[i] == '(')prevc++;
        else prevc--;
        prevm = min(prevm, prevc);
    }
    if(prevc == 0 && prevm >= 0)
        cout<<"possible\n";
    else cout<<"impossible\n";
   
    //cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
