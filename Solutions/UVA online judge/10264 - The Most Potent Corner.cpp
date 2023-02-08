#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1205

int main()
{
    int n;
    while(cin>>n)
    {
        int x;
        vector<int> c,op;
        for(int i=0;i<(1<<n);i++)
        {
            cin>>x;
            c.push_back(x);
        }
        for(short i=0;i<(1<<n);i++)
        {
            int sum=0;
            for(unsigned int j=0;j<(1<<n);j++)
            {
                if(i==j)continue;
                int S=(i^j);
                //Chequear si es potencia de 2 (solo un bit distinto)
                if((S &( S -1)) == 0)
                {
                    sum+=c[j];
                }
            }
            op.push_back(sum);
        }
        int maxi=0;
        for(short i=0;i<(1<<n);i++)
        {
            int sum=0;
            for(unsigned int j=0;j<(1<<n);j++)
            {
                if(i==j)continue;
                int S=(i^j);
                if((S &( S -1)) == 0)
                {
                    maxi=max(maxi,op[i]+op[j]);
                }
            }
        }
        cout<<maxi<<"\n";
    }
}
