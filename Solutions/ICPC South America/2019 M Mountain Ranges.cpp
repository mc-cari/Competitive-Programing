#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8

int main()
{
    int n,m,x;
    vl c;
    cin>>n>>m;

    for(int i=0;i<n;i++)
    {
        cin>>x;
        c.push_back(x);
    }
    int maxi=0;
    int prev=0;
    for(int i=1;i<n;i++)
    {
        if(c[i]-c[i-1]>m)
        {
          maxi=max(maxi,i-prev);
          prev=i;
        }
    }
    maxi=max(maxi,n-prev);
    cout<<maxi<<"\n";
}
