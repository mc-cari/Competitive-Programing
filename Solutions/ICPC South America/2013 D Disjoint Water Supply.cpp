#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
int memo[1100][1100];
//https://www.urionlinejudge.com.br/judge/es/problems/view/1493
int DP(int i, int j,vector<vl>&grafo)
{
    if(i<j)swap(i,j);
    if(memo[i][j]!=-1)return memo[i][j];
    ll sum=0;
    if(i==0)sum = 1;
    else if(i==j)sum = 0;
    else
    {
        for(int k=0;k<grafo[i].size();k++)
        {
            sum+=DP(grafo[i][k],j,grafo);
        }
        if(sum!=0)sum=1;
    }
    return memo[i][j]=sum;

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll v,x,y,e,a,b;
	while(cin>>v>>e)
    {
        memset(memo,-1,sizeof(memo));
        vector<vl > grafo(v,vl(0));
        for(int i=0;i<e;i++)
        {
            cin>>x>>y;
            grafo[y-1].push_back(x-1);
        }
        ll sum=0;
        for(int i=0;i<v-1;i++)
        {
            for(int j=i+1;j<v;j++)
            {
                if(i==0)
                {
                    sum++;
                    continue;
                }
                sum+=DP(j,i,grafo);
            }
        }
        cout<<sum<<"\n";
    }

	return 0;
}
