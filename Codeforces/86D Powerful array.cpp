#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 


ll block; 
vl ans;
vl elements(1e6+2, 0);

struct Query 
{ 
    int L, R, id; 
}; 

bool compare(Query x, Query y) 
{ 
    if (x.L/block != y.L/block) 
        return x.L/block < y.L/block; 
  
    return x.R < y.R; 
} 
ll add(vl& a, int id)
{
    return (2 * elements[a[id]] + 1) * a[id];
}
ll remove(vl& a, int id)
{
    return (-2 * elements[a[id]] + 1) * a[id];
}
  
void queryResults(vl& a, vector<Query>& q) 
{ 

    block = (int)sqrt(a.size()); 
    ans.assign(q.size(),0);

    sort(ALL(q), compare); 
   
    ll currL = 0, currR = 0; 
    ll currans = 0; 
  
    for (int i=0; i<q.size(); i++) 
    { 
        // L and R values of current range 
        int L = q[i].L, R = q[i].R; 
  
        while (currL < L) 
        { 
            currans += remove(a, currL);
            elements[a[currL]]--;
            currL++; 
        } 
        while (currL > L) 
        { 
            currans += add(a, currL-1);
            elements[a[currL-1]]++;
            currL--; 
        } 
        while (currR <= R) 
        { 
            currans += add(a, currR);
            elements[a[currR]]++;
            currR++; 
        } 
        while (currR > R+1) 
        { 
            currans += remove(a, currR-1); 
            elements[a[currR-1]]--;
            currR--; 
        } 
  
        ans[q[i].id] = currans;
    } 
} 
  
int main() 
{ 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, t, x, y;
    vl c;
    cin >> n >> t;
    for(int i = 0; i < n; i++)
    {
        cin >> x;
        c.push_back(x);

    }
    Query q;
    vector<Query>Q;
    for(int i = 0; i < t; i++)
    {
        cin >> q.L >> q.R;
        q.L--; q.R--;
        q.id = i;
        Q.push_back(q);
    }
    queryResults(c, Q);
    for(int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << "\n";
    } 
    return 0; 
} 
