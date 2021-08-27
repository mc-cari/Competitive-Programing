#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1768
int main()
{
    int n,t;
    cin>>t;
    while(t--){
        cin>>n;
        int A [2*n][2*n],B[2*n][2*n];
        int ans = -INF;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            A[i][j+n]=A[i][j];
        }
        for (int i = 0; i < n; i++) for (int j = 0; j < n*2; j++)
        {
            A[i+n][j]=A[i][j];
        }
        for (int i = 0; i < n*2; i++) for (int j = 0; j < n*2; j++)
        {
            B[i][j]=A[i][j];
            if (j > 0) B[i][j] += B[i][j-1]; //Acum sum per Row
        }
        for (int l = 0; l < n; l++) for (int r = l; r < l+n; r++)
        {
            for(int init=0; init<n;init++){
                int sum = B[init][r];
                int SubAns = B[init][r];
                if (l > 0){ sum -= B[init][l-1]; SubAns -= B[init][l-1]; }
                for (int row = init+1; row < init+n; row++)
                {
                    int aux = B[row][r];
                    if(l > 0) aux -= B[row][l-1];
                    sum = max(sum + aux, aux);
                    SubAns = max (SubAns, sum);
                }
                ans = max(ans, SubAns);
            }
        }
        cout << ans << "\n";
    }
}
