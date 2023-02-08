 #include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
int V[10000],W[10000],M[102][10202];
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1760
int n,m,cont,D;

// Top Down
int DP(int i, int c)
{
    if(i==n)
    {
        if(m>2000&&m<2200&&c<=2000&&c>m-200)return -INF;
        return 0;
    }
    if(c==m)return 0;
	if(M[i][c] != -1) return M[i][c];

	M[i][c] = DP(i+1,c);
	if(c + W[i]<=m ){
        M[i][c] = max(M[i][c],DP(i+1,c+W[i])+V[i]);
	}
	return M[i][c];
}

int main()
{
    while(cin>>m>>n){
        memset(M,-1,sizeof(M));
        int val[n];
        int wt[n];
        if(m>1800)m+=200;
        for(int i=0;i<n;i++)
        {
            cin>>W[i]>>V[i];
        }
        cout<<DP(0,0)<<"\n";


    }
    return 0;
}
