#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef int ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
typedef vector<pll> vp;
typedef double db;

#define INF 1e8
#define EPS 1e-7 
#define ALL(x) x.begin(), x.end()
#define ALLR(x) x.rbegin(), x.rend()
#define pb push_back
#define rep(i, n) for(int i = 0; i < (int)n; i++)
#define repx(i, a, b) for(int i = (int)a; i < (int)b; i++)

ll mini = 20, sum = 0;
vl spaces(13, 0);
map<pair<ll, vector<ll>>, bool> memo;
set<pair<ll, vector<ll>>> memo2;
void back(ll level, vl& sizes){
    /*cout << level << " " << sum << " " << col << endl;
    rep(i, sizes.size()) cout << sizes[i] << "*";
    cout << "\n";
    repx(i, 1, 4) cout << spaces[i] << "_";
    cout << "\n";*/
    if(level > 12) return ;
    if(sum == 0) {
        //cout << level << " " << col << "\n";
        mini = min(mini, level);
        return;
    }
    if(memo[{level, sizes}]) return;
    repx(i, 0, sizes.size()){
        
        if(sizes[i] && spaces[level] >= i+2){
            sizes[i]--;
            spaces[level] -= i+2;
            sum--;
            
            back(level, sizes);
            sum++;
            spaces[level] += i+2;
            sizes[i]++; 
            if(level >= mini) return;
        }
    }
    
    back(level+1, sizes);
    memo[{level, sizes}] = true;
}

int main() {
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

    repx(i, 1, 13)spaces[i] = i+1;
    vl sizes;
    ll n, cont = 0;
    cin >> n;
    rep(i, n){
        ll x;
        cin >> x;
        sizes.pb(x);
        cont += x * (i+2);	
        sum += x;

        if((i+1 == 12 && sizes[i] > 1) || (i+1 == 11 && sizes[i] > 2) || (i+1 == 10 && sizes[i] > 3) || (i+1 == 9 && sizes[i] > 4) || (i+1 == 8 && sizes[i] > 5) || (i+1 == 7 && sizes[i] > 6)){
            cout << "impossible\n";
            return 0;
        }
    }

    if(cont > 90) {
        cout << "impossible\n";
        return 0;
    }

    back(1, sizes);
    if(mini != INF)
        cout << mini << "\n";
    else
        cout << "impossible\n";
    return 0;
}