#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2613
int V[10000],W[10000],M[210][10202][40];
int N,x,T,K,y;
int cost(int w)
{
    return ceil((w+T*(N+1))*1.1L);
}
// Top Down
int DP(int i, int c, int cont)
{
    //cout<<i<<" "<<c<<" "<<cont<<"\n";
    if(cont==2*(N+1))return 0;
    if(i==-1)
    {
        return 0;
    }
    if(cost(c)==(N+1)*x)return 0;
	if(M[i][c][cont] != -1) return M[i][c][cont];

	M[i][c][cont] = DP(i-1,c,cont);
	if(cost(W[i]+c)<=(N+1)*x){
        M[i][c][cont] = max(M[i][c][cont],DP(i-1,c+W[i],cont+1)+V[i]);
	}
	return M[i][c][cont];
}

int main()
{

    while(cin>>N>>x>>T>>K)
    {

        if(N+x+T+K==0)break;
        memset(M,-1,sizeof(M));
        for(int i=0;i<K;i++)
        {
            cin>>W[2*i];
            W[2*i+1]=W[2*i];
            int sum=0;
            for(int j=0;j<N+1;j++)
            {
                cin>>y;
                sum+=y;
            }
            V[2*i]=sum;
            V[2*i+1]=sum;
        }
        double ans=DP(2*K-1,0,0);
        cout<<fixed<<setprecision(2)<<ans/(N+1)<<"\n";
    }

    return 0;
}
