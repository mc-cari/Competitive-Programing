#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e10
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1696
int main()
{
    ll t;
    cin>>t;
    while(t--)
    {
        ll A,B,C;
        cin>>A>>B>>C;
        ll D[A][B][C];
        for (ll i = 0; i < A; i++)for (ll j = 0; j < B; j++) for (ll z = 0; z < C; z++)
        {
            ll sum=0;
            cin >> D[i][j][z];
            if(j>0) sum += D[i][j-1][z];
            if (z>0) sum += D[i][j][z-1];
            if (j > 0 && z > 0) sum-=D[i][j-1][z-1];
            D[i][j][z]+=sum;
        }
        ll ans=-INF;

        for (ll lx = 0; lx < B; lx++) for (ll ly = 0; ly < C; ly++)for (ll rx = lx; rx < B; rx++) for (ll ry = ly; ry < C; ry++)
        {
            ll SubAns=D[0][rx][ry],sum=D[0][rx][ry],auxs=0;
            if(lx>0) auxs -= D[0][lx-1][ry];
            if (ly>0) auxs -= D[0][rx][ly-1];
            if (lx > 0 && ly > 0) auxs+=D[0][lx-1][ly-1];
            SubAns+=auxs;sum+=auxs;
            for (ll row = 1; row < A; row++)
            {
                ll aux = D[row][rx][ry];
                if(lx>0) aux -= D[row][lx-1][ry];
                if (ly>0) aux -= D[row][rx][ly-1];
                if (lx > 0 && ly > 0) aux+=D[row][lx-1][ly-1];
                sum = max(sum + aux, aux);
                SubAns = max (SubAns, sum);
            }
            ans = max(ans, SubAns);
        }
        cout<<ans<<"\n";
        if(t!=0)cout<<"\n";
    }

}
