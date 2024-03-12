#include "../Header.cpp"

// limit
log(valor maximo/precision)/log(2)
                            /log(3/2) //for ternary

ll l = 0, r = n-1, res = -1;
while(l <= r)
{
    ll p = (l + r) / 2;
    if(c[p] <= m)
        l = p+1;
    else r = p-1;
}


db l = 0, r = PI/2, mini = 1e10;

rep(i, 101)
{
    db d=(r-l)/3.0,m1=l+d,m2=r-d;
    db c1 = value(m1), c2 = value(m2);
    // Para el maximo cambiar r-m2 con l-m1
    if (c1 < c2) r = m2;
    else l = m1;
    mini = min(mini, (c1+c2)/2.0);
}

// non continuous, only work if every value is different
ll = 1,r = m, mini = 1e17;
while(l <= r)
{
    ll d = (r-l)/3;
    ll m1 = l+d, m2 = r-d;
    ll c1 = value(m1), c2 = value(m2);
    // Para el maximo cambiar r-m2 con l-m1
    if (c1 < c2) r = m2-1;
    else l = m1+1;
    mini = min(mini, min(c1,c2));
}
ans += mini;
