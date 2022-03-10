#include <bits/stdc++.h>
//https://www.urionlinejudge.com.br/judge/es/problems/view/2903
using namespace std;
typedef long long ll;

int main() {
    string x="",y;
    cin>>y;
    ll n=36000;
    for(int i=0;i<y.length();i++)
    {
        if(y[i]!='.')x+=y[i];
    }
    ll a=stoll(x);
    cout<<(n)/__gcd(a,n)<<"\n";
}
