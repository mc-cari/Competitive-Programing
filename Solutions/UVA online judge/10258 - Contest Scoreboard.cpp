#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e10
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1199
int main()
{
    int t,x,median;
    double in=0;
    priority_queue <int>maxi;
    priority_queue<ll,vector<ll>,greater<ll> >mini;
    while(cin>>x)
    {
        if(mini.empty()||x>=mini.top())
        {
            if(mini.size()==maxi.size())
            {
                mini.push(x);
            }
            else
            {
                mini.push(x);
                maxi.push(mini.top());
                mini.pop();
            }
        }
        else
        {
            maxi.push(x);
            if(mini.size()<maxi.size())
            {
                mini.push(maxi.top());
                maxi.pop();
            }
        }
        if(mini.size()>maxi.size())
        {
            cout<<mini.top()<<"\n";
        }
        else cout<<(maxi.top()+mini.top())/2<<"\n";

    }
}
