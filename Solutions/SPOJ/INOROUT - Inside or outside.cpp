#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://www.spoj.com/problems/INOROUT/
struct Point{
    ll x,y;
};
ll cross(Point a, Point b, Point c)
{
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dy0 * dx1;
}

int main()
{
    int n,q;
    Point a;
    cin>>n>>q;
    vector<Point >poligon;
    for(int i=0; i<n;i++)
    {
        cin>>a.x>>a.y;
        poligon.push_back(a);
    }
    poligon.push_back(poligon[0]);
    while(q--)
    {
        int x,y;
        cin>>a.x>>a.y;
        bool o=1;
        for(int i=0;i<n;i++)
        {
            if(cross(poligon[i],poligon[i+1],a)<0)
            {
                o=0;
            }
        }
        if(o)
        {
            cout<<"D\n";
        }
        else cout<<"F\n";

    }

}
