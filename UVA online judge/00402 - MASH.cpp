#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
using namespace std;

typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e5
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=343

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, x, cas = 1;
    while(cin >> n >> x)
    {
        vl c;
        ll y;
        for(int i = 0; i < 20; i++)
        {
            cin >> y;
            c.push_back(y);
        }
        ll card = 0, pend = c[0], pos = 0;
        vl el(n, 0);
        for(int i = 0; i < n - x; i++)
        {
            pend = c[card];
            while(1){
                if(!el[pos])
                {
                    pend--;
                    if(pend == 0)
                    {
                        el[pos] = 1;
                        
                        if(pos == n-1)
                        {
                            card++;
                            if(card == 20)break;
                            pend = c[card];
                        }
                        pos++;
                        pos%= n;
                        break;
                    }
                }
                if(pos == n-1)
                {
                    card++;
                    if(card == 20)break;
                    pend = c[card];
                }
                pos++;
                pos %= n;
            }
            if(card == 20)break;
        }
        vl ans;
        for(int i = 0; i < n; i++)
        {
            if(!el[i])ans.push_back(i);
        }
        cout<<"Selection #"<<cas<<"\n";
        for(int i = 0; i < ans.size(); i++)
        {
            cout<<ans[i]+1;
            if(i < ans.size() -1)cout<<" ";
            else cout << "\n";
        }
        cout<<"\n";
        cas++;
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

