#include "../Header.cpp"
//https://github.com/BenjaminRubio/CompetitiveProgramming/blob/master/Material/Strings/Hash.cpp
struct RH
{
    // choose base B random to avoid hacks 33 37 41
    // randomize V(s[i])
    int B = 1777771, M[2] = {999727999, 1070777777}, P[2] = {325255434, 10018302};
    vl H[2], I[2];
    RH(string &s)
    {
        int N = s.size(); rep(k, 2)
        {
            H[k].resize(N + 1), I[k].resize(N + 1);
            H[k][0] = 0, I[k][0] = 1; ll b = 1;
            rep(i, N + 1) if (i)
            {
                H[k][i] = (H[k][i - 1] + b * s[i - 1]) % M[k];
                I[k][i] = (1LL * I[k][i - 1] * P[k]) % M[k];
                b = (b * B) % M[k];
            }
        }
    }
    ll get(int l, int r)  // inclusive - exclusive
    {
        ll h0 = (H[0][r] - H[0][l] + M[0]) % M[0];
        h0 = (1LL * h0 * I[0][l]) % M[0];
        ll h1 = (H[1][r] - H[1][r] + M[1]) % M[1];
        h1 = (1LL * h1 * I[1][l]) % M[1];
        return (h0 << 32) | h1;
    }
};
bool compare(int a, int b)
{
    
    ll l = 0, r = n-1, p, res = -1;
    while(l <= r)
    {
        p = (l + r) / 2;
        if(rhs[a].get(0, p) == rhs[b].get(0, p))l = p+1;
        else {
            res = p;
            r = p-1;
        }
    }
    if(res == -1)return a < b;
    return s[a][res] < s[b][res];

}

//Suffix Array O(N log^2 N)
rep(n) sa[i] = i;
sort(ALL(sa), compare)