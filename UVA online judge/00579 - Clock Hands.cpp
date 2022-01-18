#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=520
int main()
{
    string s;
    while(cin>>s)
    {
        if(s=="0:00")break;
        int H,M;
        if(s.length()==5)
        {
            H=stoi(s.substr(0,2));
            M=stoi(s.substr(3,2));
        }
        else
        {
            H=stoi(s.substr(0,1));
            M=stoi(s.substr(2,2));
        }
        double ah=H*30,am=(360/60)*M;
        if(M!=0)
        {
            ah+=(M/60.0)*(30);
        }
        double ans=min(abs(am-ah),360-abs(am-ah));
        cout<<fixed<<setprecision(3)<<ans<<"\n";

    }


}
