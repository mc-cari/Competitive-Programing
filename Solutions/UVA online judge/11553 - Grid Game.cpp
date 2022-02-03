#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2548
int main() {

    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int c[n][n];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cin>>c[i][j];
        vl perm;
        for(int i=0;i<n;i++)
        {
            perm.push_back(i);
        }
        int mini=INF;
        do
        {
            int sum=0;
            for(int i=0;i<n;i++)
            {
                sum+=c[i][perm[i]];
            }
            mini=min(mini,sum);
        }while(next_permutation(ALL(perm)));
        cout<<mini<<"\n";
    }
}
