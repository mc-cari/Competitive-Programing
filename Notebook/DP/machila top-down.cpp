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


// Top Down
int DP(int i, int c)
{
    if(i==-1)
    {
        return 0;
    }
    if(c==0)return 0;
	if(M[i][c] != -1) return M[i][c];

	M[i][c] = DP(i-1,c);
	if(W[i]<=c){
        M[i][c] = max(M[i][c],DP(i-1,c-W[i])+V[i]);
	}
	return M[i][c];
}

int main()
{

    return 0;
}
