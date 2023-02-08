#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
//#define INF 1e17
#define INF32 INT_MAX
//#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)

const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

ll n, k;
db p;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k >> p;    
    vector<vector<db>>g;
    vl ids((1 << n), 0);
    ll in = 0;
    for(int x = 0; x < (1 << n); x++){
        ll cont = 0;

        for(int j = 0; j < n; j++){
            if((1 << j) & x) cont++;
        }

        if(cont < k){
            ids[x] = in;
            in++;
        
        }
    }

    for(int x = 0; x < (1 << n); x++){
        ll cont = 0;
        vector<db> row(in+1, 0);
        row[in] = 1;
        for(int j = 0; j < n; j++){
            if((1 << j) & x) cont++;
        }

        if(cont < k){
            row[ids[x]] = 1;
            ll x2 = x/2;
            cont = 0;
            for(int j = 0; j < n; j++){
                if((1 << j) & x2) cont++;
            }
            
            row[ids[x2]] -= 1-p;

            x2 += (1 << (n-1));
            if(cont+1 != k) row[ids[x2]] -= p;
            g.push_back(row);
        }
    }


    
   

    vector<db> ans2;
    gauss(g, ans2);


    cout << fixed << setprecision(10) << ans2[0] << "\n";
}