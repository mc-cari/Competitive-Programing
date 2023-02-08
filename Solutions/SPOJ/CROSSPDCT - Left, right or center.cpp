#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
//https://www.spoj.com/problems/CROSSPDCT/
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
    Point v1,v2;
    int x,y;
    cin>>x>>y;
    v1.x=x;v1.y=y;
    cin>>x>>y;
    v2.x=x;v2.y=y;
    int q;
    cin>>q;
    while(q--)
    {
        Point a;
        cin>>x>>y;
        a.x=x;a.y=y;
        ll ans = cross(v1,v2,a);

        if(ans > 0)
            cout << "I\n";
        else if ( ans < 0)
            cout << "D\n";
        else cout << "C\n";
    }
}
