#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3644
int main()
{
    string s;
    priority_queue<pll,vector<pll>,greater<pll> >q;
    while(cin>>s)
    {
        if(s=="#")break;
        int x,y,aux;
        cin>>x>>y;
        aux=y;
        while(y<=3000)
        {
            q.emplace(y,x);
            y+=aux;
        }
    }
    int n;
    cin>>n;
    while(n--)
    {
        cout<<q.top().second<<"\n";
        q.pop();
    }

}
