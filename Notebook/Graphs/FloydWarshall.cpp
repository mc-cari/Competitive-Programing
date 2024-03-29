#include "../Header.cpp"

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
    rep(i, n)
    {
        g[i][i] = 0;
        //g[i][i] = INF;  Detect cheapest positive cycle for each i
    }
    rep(i, m)
    {
        cin >> x >> y >> w;
        g[x][y] = min(g[x][y], w); // handle repeats
    }

    
    rep(i, n)
        rep(j, n)
            p[i][j] = i;


    rep(k, n)
        rep(i, n)
            rep(j, n)
                //g[i][j] |= (g[i][k] & g[k][j]); to find i is connected with j
                // if at the end g[i][j] & g[j][i], i and j are in the same SCC

                // To find minimal max edge in path from i to j
                //g[i][j] = min(g[i][j], max(g[i][k], g[k][j])); 

                if(g[i][k] + g[k][j] < g[i][j])
                {
                    g[i][j] = g[i][k] + g[k][j];
                    p[i][j] = p[k][j];
                    
                }
                        
    rep(k, n)
        rep(i, n)
            rep(j, n)
                if(g[i][k] != INF && g[k][j] !=INF
                    && g[k][k] < 0)
                        g[i][j] = -INF;
   rep(i, q)
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
