#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e9

// From Competitive Programing 4 book


ll p[500][500];
void printPath(int i, int j)
{
    if(i != j) printPath(i, p[i][j]);
    cout << j+1 << " ";
}

int main()
{
    int n, m, q, x ,y ,w;

    
    vector<vl > g(n, vl(n, INF));
    for(int i = 0; i < n; i++)
    {
        g[i][i] = 0;
        //g[i][i] = INF;  Detect cheapest positible cycle for each i
    }
    for(int i = 0; i < m; i++)
    {
        cin >> x >> y >> w;
        g[x][y] = min(g[x][y], w); // for repeats
    }

    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            p[i][j] = i;


    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                //g[i][j] |= (g[i][k] & g[k][j]); to find i is connected with j
                // if at the end g[i][j] & g[j][i], i and j are in the same SCC

                // To find minimal max edge in path from i to j
                //g[i][j] = min(g[i][j], max(g[i][k], g[k][j])); 

                if(g[i][k] + g[k][j] < g[i][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                    p[i][j] = p[k][j];
                    
                }
                        
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(g[i][k] != INF && g[k][j] !=INF
                    && g[k][k] < 0)
                        g[i][j] = -INF;
    for(int i = 0; i < q; i++)
    {
        cin >> x >> y;
        if(g[x][y] == INF)
            cout << "Impossible\n";
        else if (g[x][y] == -INF)
            cout << "-Infinity\n";
        else
            cout << g[x][y] << "\n";
    }

    
	return 0;
}
