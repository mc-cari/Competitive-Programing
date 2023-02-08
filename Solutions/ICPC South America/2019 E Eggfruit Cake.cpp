#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//https://matcomgrader.com/problem/9638/eggfruit-cake/
int main() {
    string x;
    ll n;
    cin>>x>>n;
    x+=x;
    vector<ll>c(x.length(),-1);
    ll prev=-1;
    for(int i=x.length()-1;i>=0;i--)
    {
        if(x[i]=='E')prev=i;
        c[i]=prev;
    }
    for(int i=0;i<x.length();i++)
    {
        if(c[i]==-1)c[i]=prev+x.length();
    }
    ll sum=0;
    for(int i=0;i<x.length()/2;i++)
    {
        if(c[i]-i<n)
            sum+=n-(c[i]-i);
    }
    cout<<sum<<"\n";
    return 0;
}
