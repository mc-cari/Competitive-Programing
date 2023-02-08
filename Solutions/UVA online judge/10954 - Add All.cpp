#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1895
int main()
{
    int n;
    priority_queue<ll,vector<ll>,greater<ll> >q;
    while(cin>>n)
    {
        if(n==0)break;
        int x;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            q.push(x);
        }
        ll sum=0;
        while(q.size()>1)
        {
            int a,b;
            a=q.top();
            q.pop();
            b=q.top();
            q.pop();
            sum+=a+b;
            q.push(a+b);
        }
        q.pop();
        cout<<sum<<"\n";
    }

}
