#include "../Header.cpp"

struct UF{
    vl p, r, sz;
    UF(ll n)
    {
        r.assign(n, 0);
        sz.assign(n, 1);
        for(ll i = 0; i < n; i++)
            p.push_back(i);
    }
    ll find(ll x)
        {return p[x] = p[x] == x ? x : find(p[x]);}
    void join(ll x, ll y)
    {
        if ((x = find(x)) == (y = find(y))) return;

        if(r[x] < r[y]) swap(x, y);
        if(r[x] == r[y]) r[x]++;
        p[y] = x;
        sz[x] += sz[y];
    }
};


// With rollback
struct UF{
    vl p, r, sz;
    stack<vl> S;
    UF(ll n)
    {
        r.assign(n, 0);
        sz.assign(n, 1);
        for(ll i = 0; i < n; i++)
            p.push_back(i);
    }
    ll find(ll x)
        {return p[x] == x ? x : find(p[x]);}
    void join(ll x, ll y)
    {
        if ((x = find(x)) == (y = find(y))) return;

        if(r[x] < r[y]) swap(x, y);
        if(r[x] == r[y]) r[x]++;
        S.push({x, y, p[x], p[y]});
        p[y] = x;
        
        sz[x] += sz[y];
    }
    void rollback()
    {
        auto a = S.back(); S.pop();
        p[a[0]] = a[2];
        p[a[1]] = a[3];
    }
};
