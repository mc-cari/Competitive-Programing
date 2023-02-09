#include "../Header.cpp"

struct SegmentTree{

    vector<ll>ST;
    int N;
    SegmentTree(int Size)
    {
        N = Size;

        ST.assign(4*N,0);
    }
    void upd(int i, ll v)
    {
        return upd(1,0,N-1,i,v);
    }
    void upd(int n, int l, int r, int i, ll v)
    {
        if(i < l || r < i) return;

        if(l == r)
        {
            ST[n] += v;
            return;
        }

        upd(2*n,l,(l+r)/2,i,v);
        upd(2*n+1,(l+r)/2+1,r,i,v);

        ST[n] = ST[2*n]+ST[2*n+1];
    }
    ll qry(int i,int j)
    {
        return qry(1,0,N-1,i,j);
    }
    ll qry(int n, int l, int r, int i, int j)
    {
        if(r < i || j < l)
            return 0;

        if(i <= l && r <= j)
            return ST[n];

        return query(2*n,l,(l+r)/2,i,j)+query(2*n+1,(l+r)/2+1,r,i,j);
    }
};
struct SegmenTree2D
{
    vector<SegmentTree>ST;
    int N;
    SegmenTree2D(int Size)
    {
        N = Size;
        ST.resize(4*N,Size);
    }

    void update(int i, int j, int v)
    {
        return update(1,0,N-1,i,j,v);
    }
    void update(int n, int l, int r, int i, int j, ll v)
    {
        if(i < l || r < i) return;

        if(l == r)
        {
            ST[n].update(j,v);
            return;
        }

        update(2*n,l,(l+r)/2,i,j,v);
        update(2*n+1,(l+r)/2+1,r,i,j,v);

        ST[n].update(j,v);
    }
    ll query(int i1, int i2, int j1, int j2)
    {
        return query(1,0,N-1,i1,i2,j1,j2);
    }
    ll query(int n, int l, int r, int i1, int i2, int j1, int j2)
    {
        if(l > j1 || i1 > r)
            return 0;
        if(i1 <= l && r <= j1)
        {
            return ST[n].query(i2,j2);
        }
        return query(2*n,l,(l+r)/2,i1,i2,j1,j2)+query(2*n+1,(l+r)/2+1,r,i1,i2,j1,j2);
    }
};
int main()
{
    ll q, n, x, y, l, b, r, t, a;
    SegmenTree2D ST(1025);
    while(cin >> q)
    {
        if(q == 0)
        {
            cin >> n;
        }
        else if(q == 1)
        {
            cin >> x >> y >> a;
            ST.update(x, y, a);
        }
        else if(q == 2)
        {
            cin >> l >> b >> r >> t;
            cout << ST.query(l, b, r, t) <<"\n";
        }
        else
            break;
        /*for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout<<ST.query(i,j,i,j)<<" ";
            }cout<<endl;
        }*/
    }
    return 0;
}
