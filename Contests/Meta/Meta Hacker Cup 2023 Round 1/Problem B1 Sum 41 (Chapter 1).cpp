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

vector<int> primeFactors(ll n)  
{    
    vector<int> mp;
    while (n % 2 == 0)  
    {  
        n = n/2; 
        mp.pb(2); 
    }  
  
    for (int i = 3; i <= sqrt(n); i = i + 2)  
    {   
        while (n % i == 0)  
        {  
            mp.pb(i);
            n = n/i;  
        }  
    }  
  
    if (n > 2)  
        mp.pb(n);
    
    return mp;
}

vector<int> res;
bool o = 0;

void Partition(vector<int> &set, int index,
               vector<vector<int> >& ans, int sum, vector<int>& muls)
{
    if(o || sum > 41)
        return;
    
    if (index == set.size()) {
        
        if(sum <= 41)
        {
            rep(i, 41 - sum)
                res.pb(1);

            for(auto it : muls)
                res.pb(it);

            if(res.size() <= 100)
                o = 1;
            else
                res.clear();
        }
        return;
    }
 
    for (int i = 0; i < ans.size(); i++) {
        ans[i].push_back(set[index]);
        sum -= muls[i];
        muls[i] = (muls[i] * set[index]);
        sum += muls[i];
        
        Partition(set, index + 1, ans, sum, muls);
        sum -= muls[i];
        muls[i] = (muls[i] / set[index]);
        sum += muls[i];
        ans[i].pop_back();
    }
 
    ans.push_back({ set[index] });
    muls.push_back(set[index]);
    sum += set[index];
    Partition(set, index + 1, ans, sum, muls);
    sum -= set[index];
    muls.pop_back();
    ans.pop_back();
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    repx(T, 1, t+1)
    {
        ll P;
        cin >> P;
        vector<int> mp = primeFactors(P);

        int sum = 0;
        for (auto it : mp)
            sum += it;

        if(sum > 41)
        {
            cout << "Case #" << T << ": " << "-1" << "\n";
            continue;
        }

        res.clear();
        o = 0;
        vector<vector<int>>ans;
        vector<int>mul;
        Partition(mp, 0, ans, 0, mul);

        if(res.size() > 0)
        {
            cout << "Case #" << T << ": " << res.size();
            for(auto it : res)
                cout << " " << it;
            cout << "\n";
            
        }
        else{
            cout << "Case #" << T << ": " << "-1" << "\n";
        }
    }
    
}