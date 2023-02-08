#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3836
int main()
{

    int t;
    cin>>t;
    for(int T=1;T<=t;T++)
    {
        int n;
        cin>>n;
        string s;
        cin>>s;
        int cont=0;
        for(int i=0;i<n;i++)
        {
            if(s[i]=='.')
            {
                i+=2;
                cont++;
            }
        }
        cout<<"Case "<<T<<": ";
        cout<<cont<<"\n";
    }
}
