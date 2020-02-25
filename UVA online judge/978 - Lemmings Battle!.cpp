#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=919
int main() {
    int n,t;cin>>t;
    while(t--)
    {
        int B,a,b,x;
        cin>>B>>a>>b;
        priority_queue<int>q1,q2;
        while(a--)
        {
            cin>>x;
            q1.push(x);
        }
        while(b--)
        {
            cin>>x;
            q2.push(x);
        }
        while(1)
        {
            vl p1,p2;
            for(int i=0;i<B;i++){
                a=q1.top(),b=q2.top();
                q1.pop();q2.pop();
                if(a>b)
                {
                    p1.push_back(a-b);
                }
                else if(b>a)p2.push_back(b-a);
                if(q1.empty()||q2.empty())break;
            }
            for(int i=0;i<p1.size();i++)q1.push(p1[i]);
            for(int i=0;i<p2.size();i++)q2.push(p2[i]);
            if(q1.empty()||q2.empty())break;

        }
        if(q1.size()>q2.size())
        {
            cout<<"green wins\n";
            while(!q1.empty())
            {
                cout<<q1.top()<<"\n";
                q1.pop();
            }
        }
        else if(q1.size()<q2.size())
        {
            cout<<"blue wins\n";
            while(!q2.empty())
            {
                cout<<q2.top()<<"\n";
                q2.pop();
            }
        }
        else cout<<"green and blue died\n";
        if(t!=0)cout<<"\n";
    }


}
