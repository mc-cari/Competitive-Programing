#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e5
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/gym/103185/problem/J

unordered_map<bitset<80>, ll> m;

void add(vl& d, bitset<80>& aux, ll pos)
{
    if(pos == 8)
    {
        m[aux]++;
        return;
    }
    for(int i = 0; i <= d[pos]; i++)
    {

        aux.set (pos * 9 + i, 1);
        add(d, aux, pos+1);
        aux.set (pos * 9 + i, 0);
    }
}

void res(vl& d, bitset<80>& aux, ll pos)
{
    if(pos == 8)
    {
        m[aux]--;
        return;
    }
    for(int i = 0; i <= d[pos]; i++)
    {

        aux.set (pos * 9 + i, 1);
        res(d, aux, pos+1);
        aux.set (pos * 9 + i, 0);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll n, k;
    cin >> n >> k;
    vector<vl> ssd;
    for(int i = 0; i < n; i++)
    {
        char c;
        ll x, y;
        cin >> c;
        if(c == 'C')
        {
            cin >> y;
            vl d(8, 0);
            bitset<80>aux;
            for(int j = 0; j < y; j++)
            {
                cin >> x;
                d[x-1]++;
            }
            add(d, aux, 0);

            ssd.push_back(d);
        }
        else if(c == 'J')
        {
            cin >> y;
            vl d(8, 0);
            bitset<80>aux;
            for(int j = 0; j < y; j++)
            {
                cin >> x;
                d[x-1]++;
            }
            for(int i = 0; i < 8; i++)
            {

                aux.set(i * 9 + d[i], 1);
            }
            cout<<m[aux]<<"\n";
        }
        else
        {
            
            cin >> y;

            bitset<80>aux;
            res(ssd[y-1], aux, 0);
        }
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

