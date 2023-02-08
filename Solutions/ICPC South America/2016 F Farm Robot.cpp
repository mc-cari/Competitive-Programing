#include<bits/stdc++.h>
using namespace std;
//https://www.urionlinejudge.com.br/judge/es/problems/view/2349
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int n,c,s,x,pos=1,sum=0;
    cin>>n>>c>>s;
    if(s==1)sum++;
    for(int i=0;i<c;i++)
    {
        cin>>x;
        if(x==1)
        {
            pos++;
        }
        else
        {
            pos--;
        }
        if(pos==0)pos=n;
        if(pos==n+1)pos=1;
        if(pos==s)sum++;
    }
    cout<<sum<<"\n";
	return 0;
}
