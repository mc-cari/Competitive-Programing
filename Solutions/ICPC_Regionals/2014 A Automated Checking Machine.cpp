#include<bits/stdc++.h>
using namespace std;
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4833
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int a, b, c, d, e, A, B, C, D, E;
    while(cin>>a>>b>>c>>d>>e>>A>>B>>C>>D>>E)
    {
        if(a!=A&&b!=B&&c!=C&&d!=D&&e!=E)
            cout<<"Y\n";
        else
            cout<<"N\n";
    }
	return 0;
}
