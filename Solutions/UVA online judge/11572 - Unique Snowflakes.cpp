#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2619
int main() {
    int n,t;cin>>t;
    while(t--)
    {
        int x,prev=0,maxi=0;
        map<int,int>d;
        vl c;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
            while(d[x]!=0)
            {
                d[c[prev++]]=0;
            }
            d[x]=1;
            maxi=max(maxi,i-prev+1);
        }
        cout<<maxi<<"\n";
    }


}
