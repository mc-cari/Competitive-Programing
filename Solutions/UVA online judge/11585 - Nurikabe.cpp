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
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2632
char g[101][101];
ll val[101][101];
ll r, c;
vl d1 = {0, 1, 0, -1, 1, -1, 1, -1};
vl d2 = {1, 0, -1, 0, 1, 1, -1, -1};
ll wss, bs, num, tam, flag;
void flood_fill(int i, int j, char c1, char c2, ll type)
{
    if(g[i][j] != c1) return;
    g[i][j] = c2;

    if(type == 2)
    {
        tam++;
        if(num == -1 && val[i][j] != -1)
            num = val[i][j];
        else if(num != -1 && val[i][j] != -1)
        {
            num = -1;
            return;
        }
    }
    
    for(int z = 0; z < ((type == 3) ? 8 : 4); z++)
    {
        int x = i + d1[z];
        int y = j + d2[z];
        if(x < 0 || x == r || y < 0 || y == c)
        {
            if(type == 3) flag = 1;
            continue;
        }
        if(g[x][y] == c1)
            flood_fill(x, y, c1, c2, type);
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
        ll d, x, y, v;
        cin >> r >> c >> d;

        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                val[i][j] = -1;

        bool o = 1;
        for(int i = 0; i < d; i++)
        {
            cin >> x >> y >> v;
            val[x][y] = v;
        }
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++){
                cin >> g[i][j];
                if(val[i][j] != -1 && g[i][j] == '#')
                    o = 0;
            }


        ll b_cc = 0;
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                if(g[i][j] == '#')
                {
                    b_cc++;
                    flood_fill(i, j, '#', 'O', 1);
                }
            }
        }

        
        if(b_cc > 1)
        {
            cout << "not solved\n";
            continue;
        }
        
        for(int i = 0; i < r && o; i++)
        {
            for(int j = 0; j < c && o; j++)
            {
                if(g[i][j] == '.')
                {
                    num = -1; tam = 0;
                    
                    flood_fill(i, j, '.', 'P', 2);
                    if(tam != num) o = 0;
                }
            }
        }
        if(o == 0)
        {
            cout << "not solved\n";
            continue;
        }
        for(int i = 0; i < r && o; i++)
        {
            for(int j = 0; j < c && o; j++)
            {
                if(g[i][j] == 'P')
                {
                    flag = 0;
                    flood_fill(i, j, 'P', '.', 3);
                    if(!flag) o = 0;
                }
            }
        }
        
        if(o == 0)
        {
            cout << "not solved\n";
            continue;
        }
        for(int i = 0; i < r -1 && o; i++)
        {
            for(int j = 0; j < c-1 && o; j++)
            {
                if(!(g[i][j] == '.' || g[i+1][j] == '.' || g[i][j+1] == '.' || g[i+1][j+1] == '.'))
                    o = 0;
                
            }
        }
        if(o == 0)
        {
            cout << "not solved\n";
            continue;
        }
        cout << "solved\n";

    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
