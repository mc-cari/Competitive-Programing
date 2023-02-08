#include "../Header.cpp"

vector <bool> crib;
void criba(ll b)
{
    crib.assign(b, 1);
    crib[0] = 0;
    crib[1] = 0;
    repx(k, 2, sqrt(b+1) + 1)
        if(crib[k])
            for(int j=2; (j * k) < b + 1; j++)//optimization j=k
                crib[k*j] = 0;
}
