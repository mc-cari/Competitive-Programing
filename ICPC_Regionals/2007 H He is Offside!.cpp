#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=9
#define INF 1e12


int main()
{
    int a,d,x;
    while(cin>>a>>d)
    {
        if(a+d==0)break;
        vl A,D;
        for(int i=0;i<a;i++)
        {
            cin>>x;
            A.push_back(x);
        }
        for(int i=0;i<d;i++)
        {
            cin>>x;
            D.push_back(x);
        }
        sort(A.begin(),A.end());
        sort(D.begin(),D.end());
        if(A[0]<D[1])
        {
            cout<<"Y\n";
        }
        else
        {
            cout<<"N\n";
        }
    }


    return 0;
}

