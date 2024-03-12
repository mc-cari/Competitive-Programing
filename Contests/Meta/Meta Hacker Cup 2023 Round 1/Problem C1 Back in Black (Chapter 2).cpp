#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define INF32 INT_MAX
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    repx(T, 1, t+1)
    {
        int n;
        cin >> n;

        string s;
        cin >> s;

        int q;
        cin >> q;

        vl clicks(n, 0);


        int x;
        cin >> x;
        x--;
        for(int j = x; j < n; j += x+1)
        {
            if(s[j] == '1') s[j] = '0';
            else s[j] = '1';
        }
        ll prevans = 0, ans = 0;
        rep(i, n)
        {
            if(s[i] == '0') continue;
            ans++;
            clicks[i] = 1;
            for(int j = i; j < n; j += i+1)
            {
                if(s[j] == '1') s[j] = '0';
                else s[j] = '1';
            }
        }
        prevans = ans;
        

        rep(i, q-1) 
        {
            cin >> x;
            x--;

            if(!clicks[x])
            {
                clicks[x] = 1;
                prevans++;
            }
            else{
                clicks[x] = 0;
                prevans--;
            }
            ans += prevans;
            

        }

       

        cout << "Case #" << T << ": " << ans << "\n";
    }
    
}