#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e7
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
const double PI = acos(-1.0);

//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1149

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, m, q;
    while(cin >> n >> m >> q && (n + m + q)){
        vector<vector< char> > g(n, vector<char> (m, '.'));
        while(q--)
        {
            char c, c2 = '?';
            vector<vector<char> >aux = g;
            ll x, y, cant;
            string s;
            cin >> c >> x >> y >> cant >> s;
            ll inx = x, iny = y;
            inx--; iny--;
            int o = 0;
            vl minr(n, INF), minc(m, INF), maxr(n, -1), maxc(m, -1);
            for(int i = 0; i < cant; i++)
            {
                if(aux[inx][iny] != '.' && aux[inx][iny] != c){
                    o = 3;
                    if(c2 == '?')
                    c2 = aux[inx][iny];
                }
                if(inx < 0 || inx >= n || iny < 0 || iny >= m)
                {
                    o = 1;
                    break;
                }
                minr[inx] = min(minr[inx], iny);
                minc[iny] = min(minc[iny], inx);
                maxr[inx] = max(maxr[inx], iny);
                maxc[iny] = max(maxc[iny], inx);
                aux[inx][iny] = c;
                if(s[i] == 'B' || s[i] == 'C' || s[i] == 'D')iny++;
                if(s[i] == 'H' || s[i] == 'G' || s[i] == 'F')iny--;
                if(s[i] == 'H' || s[i] == 'A' || s[i] == 'B')inx--;
                if(s[i] == 'F' || s[i] == 'E' || s[i] == 'D')inx++;

            }
            if(inx+1 != x && iny != y)o = 2;
            if(inx < 0 || inx >= n || iny < 0 || iny >= m) o = 1;
            if(o == 0)
            {
                
                for(int i = 0; i < n; i++)
                {
                    for(int j = o; j < m; j++)
                    {
                        if(j < minr[i] || j > maxr[i] || i < minc[j] || i > maxc[j])continue;
                        if(aux[i][j] != '.' && aux[i][j] != c)
                        {
                            o = 3;
                            if(c2 == '?')
                            c2 = aux[i][j];
                        }
                        aux[i][j] = c;
                    }
                    
                }
                if(o == 0)
                    g = aux;
                else
                {
                    cout<<"REGION "<<c2<<" BOUNDARY INTERSECTS REGION "<<c<<"\n";
                }
                
            }
            else if(o == 1) cout<<"REGION "<<c<<" GOES OUTSIDE THE ARRAY\n";
            else if(o == 2) cout<<"REGION "<<c<<" BOUNDARY IS NOT CLOSED\n";
            else cout<<"REGION "<<c2<<" BOUNDARY INTERSECTS REGION "<<c<<"\n";
            
            
        }
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                cout << g[i][j];
            }cout<<"\n";
        }
    }

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
