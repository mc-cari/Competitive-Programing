#include "../Header.cpp"

//Euler Tour
vl L, R, d, c;
ll num = -1;
vector<vl>g;
void dfs(ll in, ll p)
{
    num++;
    L[in] = num;
    d.push_back(c[in]);
    for(auto it : g[in])
    {
        if(p != it)
            dfs(it, in);
    } 
    R[in] = num;
}
