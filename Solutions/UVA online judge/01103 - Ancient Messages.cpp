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

//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3544

char g[201][51*16];

ll h, w;

vl d1 = {1, -1, 0, 0};
vl d2 = {0, 0, 1, -1};


void flood_fill(ll r, ll c, char c1, char c2)
{
    if(r < 0 || c < 0 || r >= h || c >= 4*w || g[r][c] != c1) return;
    g[r][c] = c2;
    for(int i = 0; i < 4; i++)
        flood_fill(r + d1[i], c + d2[i], c1, c2);
}
ll cont = 0;
void flood_fill2(ll r, ll c, char c1, char c2)
{
    if(r < 0 || c < 0 || r >= h || c >= 4*w || g[r][c] != c1) return;
    g[r][c] = c2;
    for(int i = 0; i < 4; i++)
    {
        ll nr = r + d1[i];
        ll nc = c + d2[i];
        if(nr < 0 || nc < 0 || nr >= h || nc >= 4*w) continue;
        if(g[nr][nc] == c1)
        {
            flood_fill2(r + d1[i], c + d2[i], c1, c2);
        }
        else if(g[nr][nc] == '0')
        {
            cont++;
            flood_fill(r + d1[i], c + d2[i], '0', 'w');
        }

        
    }
        
}

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll T = 0;

	while(cin >> h >> w && (h + w)){
    
    
        for(int i = 0; i < h; i++) 
        {
            for(int j = 0; j < w; j++)
            {
                char p;
                cin >> p;
                string aux = {p};
                ll num = stoi(aux, 0, 16);
                for(int z = 0; z < 4; z++)
                {
                    if(num & (1 << z)) g[i][j*4 + (3 - z)] = '1';
                    else g[i][j*4 + (3 - z)] = '0';
                }
            }
            
        }
        for(int i = 0; i < h; i++)
        {
            flood_fill(i, 0, '0', 'b');
            flood_fill(i, w*4 - 1, '0', 'b');
        }
        for(int i = 0; i < w*4; i++)
        {
            flood_fill(0, i, '0', 'b');
            flood_fill(h - 1, i, '0', 'b');
        }
        
        string ans = "";
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w*4; j++)
            {
                if(g[i][j] != '1')continue;
                cont = 0;
                flood_fill2(i, j, '1', 't');
                if(cont == 0) ans += 'W';
                else if(cont == 1) ans += 'A';
                else if(cont == 2) ans += 'K';
                else if(cont == 3) ans += 'J';
                else if(cont == 4) ans += 'S';
                else ans += 'D';
            } 
        }
        
        
        sort(ALL(ans));
        T++;
        cout << "Case " << T << ": " << ans << "\n";
    }
	
	
	
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
}
