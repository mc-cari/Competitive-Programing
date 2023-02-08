#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=44
int main()
{
    int n;
    cin>>n;
    int B [n][n];
    int ans = -INF;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    {
        cin >> B[i][j];
        if (j > 0) B[i][j] += B[i][j-1]; //Acum sum per Row
    }
    for (int l = 0; l < n; l++) for (int r = l; r < n; r++)
    {
        int sum = B[0][r];
        int SubAns = B[0][r];
        if (l > 0){ sum -= B[0][l-1]; SubAns -= B[0][l-1]; }
        for (int row = 1; row < n; row++)
        {
            int aux = B[row][r];
            if(l > 0) aux -= B[row][l-1];
            sum = max(sum + aux, aux);
            SubAns = max (SubAns, sum);
        }
        ans = max(ans, SubAns);
    }
    cout << ans << "\n";

}
