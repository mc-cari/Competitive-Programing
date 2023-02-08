#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
int mini;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1750
vl c;
int main()
{
    int n;
    cin>>n;
    vl vis(26,0);
    c.clear();
    int x;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        vis[x+11]++;
    }
    for(int i=-11;i<=12;i++)
    {
        if(vis[i+11]%2==1)
        {
            c.push_back(i);
        }
    }
    if(c.empty())
    {
        cout<<0<<"\n";
        return 0;
    }
    mini=INF;
    int sum=0;
    for(int i=0;i<c.size()/2;i++)
    {
        sum+=min(24-abs(c[i*2]-c[i*2+1]),abs(c[i*2]-c[i*2+1]));
    }
    mini=min(mini,sum);
    sum=0;
    for(int i=0;i<c.size()/2;i++)
    {
        sum+=min(24-abs(c[(i*2+1)%c.size()]-c[(i*2+2)%c.size()]),abs(c[(i*2+1)%c.size()]-c[(i*2+2)%c.size()]));
    }
    mini=min(mini,sum);
    cout<<mini<<"\n";
}
