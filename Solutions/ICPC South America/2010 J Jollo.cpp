#include<bits/stdc++.h>
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2815
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int a,b,c,x,y;
    while(cin>>a>>b>>c>>x>>y)
    {
        if(x+y+a+b+c==0)break;
        vector<int>A={a,b,c};
        vector<int>B={x,y};
        set<int>d;
        d.insert(a);
        d.insert(b);
        d.insert(c);
        d.insert(x);
        d.insert(y);
        sort(A.rbegin(),A.rend());
        sort(B.rbegin(),B.rend());
        if(B[0]>A[0])
        {
            if(B[1]>A[0])
            {
                for(int i=1;i<=52;i++)
                {
                    if(!d.count(i))
                    {
                        cout<<i<<"\n";
                        break;
                    }
                }
            }
            else if(B[1]>A[1])
            {
                bool o=0;
                for(int i=A[1]+1;i<=52;i++)
                {
                    if(!d.count(i))
                    {
                        cout<<i<<"\n";
                        o=1;
                        break;
                    }
                }
                if (o)continue;
                cout<<"-1\n";
            }
            else
            {
                bool o=0;
                for(int i=A[0]+1;i<=52;i++)
                {
                    if(!d.count(i))
                    {
                        cout<<i<<"\n";
                        o=1;
                        break;
                    }
                }
                if (o)continue;
                cout<<"-1\n";
            }
        }
        else if(B[1]>A[1])
        {
            bool o=0;
            for(int i=A[1]+1;i<=52;i++)
            {
                if(!d.count(i))
                {
                    cout<<i<<"\n";
                    o=1;
                    break;
                }
            }
            if (o)continue;
            cout<<"-1\n";
        }
        else
        {
            cout<<"-1\n";
        }
    }
	return 0;
}
