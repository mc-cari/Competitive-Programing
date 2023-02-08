#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1625
int main()
{
    int n;
    while(cin>>n){
        if(n==0)break;
        vl A;
        int x;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            A.push_back(x);
        }
        int sum = A[0], ans = A[0];
        for (int i = 1; i < n; i++)
        {
            sum = max(A[i] + sum, A[i]); //Ignores sum if prev sum is worse than A[i]
            ans = max(ans, sum);
        }
        if(ans>0)
            cout<<"The maximum winning streak is "<<ans<<".\n";
        else cout<<"Losing streak.\n";
    }

}
