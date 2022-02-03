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

//https://open.kattis.com/problems/emptyingbaltic

ll g[501][501], d[501][501];
ll h, w;

vl d1 = {-1, -1 , -1, 0, 0, 1, 1, 1};
vl d2 = {-1, 0, 1, -1, 1, -1, 0, 1};

int main() {

	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> h >> w;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            cin >> g[i][j];
            d[i][j] = 0;
            
        }
    }
    ll x, y;
    cin >> x >> y;
    x--; y--;


    
	priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>> > q; //from low to high
    d[x][y] = g[x][y];
	q.push({d[x][y], x, y});
	

	while(!q.empty()){

		ll W;
		tie(W, x, y) = q.top();
	    q.pop();
		
		if(W != d[x][y])continue;
		for(int i = 0; i < 8; i++)
		{
            ll nx = x + d1[i];
            ll ny = y + d2[i];
            if(nx < 0 || nx >= h || ny < 0 || ny >= w)continue;
            
		   	if(d[nx][ny] > max(d[x][y], g[nx][ny]))
		   	{
		   		d[nx][ny] = max(d[x][y], g[nx][ny]);
		   		q.push({d[nx][ny], nx, ny});
			}
	    }
	}
    ll sum = 0;
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            sum -= d[i][j];
    
    cout << sum << '\n';


    
    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
