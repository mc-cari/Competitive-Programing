#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/1376
int main()
{
    int N,R,C,K;
    while(cin>>N>>R>>C>>K)
    {
        if(N+R+C+K==0)break;
        int r[R][C],tmp[R][C];
        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                cin>>r[i][j];
                tmp[i][j]=r[i][j];
            }
        }
        for(int k=0;k<K;k++)
        {

            for(int i=0;i<R;i++)
            {
                for(int j=0;j<C;j++)
                {
                    if(j!=0&&r[i][j-1]==(r[i][j]+1)%N)
                    {
                        tmp[i][j-1]=r[i][j];
                    }
                    if(i!=0&&r[i-1][j]==(r[i][j]+1)%N)
                    {
                        tmp[i-1][j]=r[i][j];
                    }
                    if(j<C-1&&r[i][j+1]==(r[i][j]+1)%N)
                    {
                        tmp[i][j+1]=r[i][j];
                    }
                    if(i<R-1&&r[i+1][j]==(r[i][j]+1)%N)
                    {
                        tmp[i+1][j]=r[i][j];
                    }
                }
            }
            for(int i=0;i<R;i++)
            {
                for(int j=0;j<C;j++)
                {
                    r[i][j]=tmp[i][j];
                }
            }

        }
        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                if(j<C-1)cout<<r[i][j]<<" ";
                else cout<<r[i][j]<<"\n";
            }
        }


    }
}
