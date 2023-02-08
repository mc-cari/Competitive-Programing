#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1271
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t=1,n,r;
    while(cin>>n)
    {
        if(n==0)break;
        cin>>r;
        vl c;
        for(int i=1;i<=n;i++)
        {
            c.push_back(i);
        }
        int x,y;
        for(int i=0;i<r;i++)
        {
            cin>>x>>y;
            x--;y--;
            reverse(c.begin()+x,c.begin()+y+1);
        }
        vl d(n+1,0);
        for(int i=0;i<c.size();i++)
        {
            d[c[i]]=i+1;
        }
        cin>>r;
        cout<<"Genome "<<t<<"\n";
        for(int i=0;i<r;i++)
        {
            cin>>x;
            cout<<d[x]<<"\n";
        }
        t++;

    }
}
