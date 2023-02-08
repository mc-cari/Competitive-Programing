#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e10
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=82
int main()
{
    string s;
    while(cin>>s)
    {
        if(s=="#")break;
        if(next_permutation(s.begin(),s.end()))
        {
            cout<<s<<"\n";
        }
        else
        {
            cout<<"No Successor\n";
        }
    }
}
