#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef double db;
#define INF 1e17
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=793
char g[9][9];
ll empty_cc = 0, w = 0, b = 0, tam;
vl d1 = {0, 1, 0, -1};
vl d2 = {1, 0, -1, 0};
ll wss, bs;
void flood_fill(int i, int j, char c1, char c2)
{
    tam++;
    g[i][j] = c2;
    for(int z = 0; z < 4; z++)
    {
        int x = i + d1[z];
        int y = j + d2[z];
        if(x < 0 || x == 9 || y < 0 || y == 9)continue;
        if(g[x][y] == c1)
            flood_fill(x, y, c1, c2);
        if(g[x][y] == 'O')
            wss = 1;
        else if (g[x][y] == 'X')
            bs = 1;
    }
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    
    while(t--)
    {
        empty_cc = 0; w = 0; b = 0;
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                cin >> g[i][j];
                if(g[i][j] == 'O')w++;
                else if(g[i][j] == 'X')b++;
                
            }
        }
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(g[i][j] == '.')
                {
                    tam = 0; wss = 0; bs = 0;
                    flood_fill(i, j, '.', '#');
                    empty_cc++;
                    if(wss == 1 && bs == 0) w += tam;
                    else if (wss == 0 && bs == 1) b += tam;
                    
                }
            }
        }
        cout << "Black " << b << " White " << w << "\n";

    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
