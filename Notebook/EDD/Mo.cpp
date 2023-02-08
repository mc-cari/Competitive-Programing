#include "../Header.cpp"

/*
 
a ancestor of b

[start[a], start[b]]


else

[end[a], start[b]] + lca(a, b)

*/  

ll block;
vl ans;
vl el(1e6+2, 0);
// F = add-remove
// O((N+Q)F√N)
struct Query 
{ 
    int L, R, id; 
}; 


bool cmp(Query a, Query b){
    if(a.L / block != b.L / block)
        return a.L < b.L;
    return a.L / block % 2 ? a.R < b.R : a.R > b.R;
}
ll add(vl& a, int id)
{
    //cout<<id<<endl;
    return (2 * el[a[id]] + 1) * a[id];
}
ll remove(vl& a, int id)
{
    return (-2 * el[a[id]] + 1) * a[id];
}
void Mo(vl& a, vector<Query>& q) 
{ 

    block = (int)sqrt(a.size()); 
    ans.assign(q.size(),0);

    sort(ALL(q), cmp); 
   
    ll cL = 0, cR = 0, cAns = 0; 
  
    for (int i=0; i<q.size(); i++) 
    { 
        // L and R values of current range 
        int L = q[i].L, R = q[i].R; 
  
        while (cR <= R) {
            cAns += add(a, cR);
            el[a[cR]]++;
            cR++; 
        }
        while (cL > L) { 
            cAns += add(a, cL-1);
            el[a[cL-1]]++;
            cL--;  
        }
        while (cR > R+1) {
            cAns += remove(a, cR-1);
            el[a[cR-1]]--;
            cR--; 
        }
        while (cL < L) {
            cAns += remove(a, cL);
            el[a[cL]]--;
            cL++; 
        }
  
        ans[q[i].id] = cAns;
    } 
} 
  
//https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/master/other/mos_algorithm.cpp

// [l,r) 
int n,sq,nq; // array size, sqrt(array size), #queries
struct qu{int l,r,id;};
qu qs[MAXN];
ll ans[MAXN]; // ans[i] = answer to ith query
bool qcomp(const qu &a, const qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}
void mos(){
    fore(i,0,nq)qs[i].id=i;
    sq=sqrt(n)+.5;
    sort(qs,qs+nq,qcomp);
    int l=0,r=0;
    init();
    fore(i,0,nq){
        qu q=qs[i];
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        ans[q.id]=get_ans();
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
    Mo(c, Q);
    for(int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << "\n";
    } 
    return 0; 
} 