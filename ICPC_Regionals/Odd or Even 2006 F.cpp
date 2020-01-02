#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=260&page=show_problem&problem=1657
int main()
{

    int n,x,par1,par2,impar1,impar2;
    while(cin>>n)
    {
        par1=0;par2=0;impar1=0;impar2=0;
        if(n==0)break;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(x%2==0)par1++;
            else impar1++;
        }
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(x%2==0)par2++;
            else impar2++;
        }
        int sum=0;
        sum+=n-min(par1,impar2)-min(par2,impar1);
        cout<<sum<<endl;

    }
    return 0;
}
