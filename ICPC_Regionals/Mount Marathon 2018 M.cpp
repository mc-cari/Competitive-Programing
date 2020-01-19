#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/2915
int main()
{
    int n,x;
    cin>>n;
    list<int> c;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        c.push_back(x);
    }
    for(int i=1;i<14;i++)
    {
        if(c.size()==1)break;
        for(list<int>::iterator it=prev(prev(c.end()));;it--)
        {
            if(*it==i&&*it>=*next(it))
            {
                c.erase(next(it));
            }
            if(it==c.begin())break;
        }
    }
    cout<<c.size()<<"\n";
}
