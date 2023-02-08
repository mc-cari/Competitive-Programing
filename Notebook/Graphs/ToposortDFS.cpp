#include "../Header.cpp"

vl s, v;
vector<vl > g;
void dfs(int t)
{
    v[t] = 1;
    for(auto it : g[t])
        if(!v[it])
            dfs(it);
    
    s.pb(t);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
	ll n;
	g.assign(n, vl());
    v.assign(n, 0);

    rep(i, n)
        if(!v[i])
            dfs(i);

    reverse(ALL(s));
	return 0;
}
