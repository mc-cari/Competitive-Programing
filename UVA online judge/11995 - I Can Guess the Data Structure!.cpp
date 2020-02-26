#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3146
int main()
{
    int n;

    while(cin>>n)
    {
        stack<int>s;
        queue<int>q;
        priority_queue<int>p;
        int x,y;
        bool o1=1,o2=1,o3=1;
        while(n--)
        {
            cin>>x>>y;
            if(x==1)
            {
                s.push(y);
                q.push(y);
                p.push(y);
            }
            else
            {
                if(s.top()!=y)
                {
                    o1=0;
                }
                if(q.front()!=y)
                    o2=0;
                if(p.top()!=y)o3=0;
                s.pop();
                q.pop();
                p.pop();
            }
        }
        if(o1+o2+o3==0)
            cout<<"impossible\n";
        else if(o1+o2+o3>1)
            cout<<"not sure\n";
        else if(o1)
            cout<<"stack\n";
        else if(o2)
            cout<<"queue\n";
        else
            cout<<"priority_queue\n";

    }

}
