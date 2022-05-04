#include <bits/stdc++.h>
using namespace std;

struct UF{
    vl p, r;
    UF(ll n)
    {
        for(ll i = 0; i < n; i++)
        {
            p.push_back(i);
            r.push_back(0);
        }
    }
    ll find(ll x)
        {return p[x] = p[x] == x ? x : find(p[x]);}
    void join(ll x, ll y)
    {
        x = find(x);
        y = find(y);
        if(x != y)
        {

            if(r[x] >= r[y])
            {
                if(r[x] == r[y]) r[x]++;
                p[y] = x;
            }
            else p[x] = y;
        }
    }
};

int main()
{
    UF ds(7);

    ds.join(0,1);
    ds.join(1,2);
    ds.join(3,4);
    ds.join(5,6);
    ds.join(4,5);
    ds.join(2,6);
    cout<<ds.find(0)+1<<endl;
    cout<<ds.find(1)+1<<endl;
    cout<<ds.find(2)+1<<endl;
    cout<<ds.find(3)+1<<endl;
    cout<<ds.find(4)+1<<endl;
    cout<<ds.find(5)+1<<endl;

    return 0;
}
