#include "../Header.cpp"

struct SegmentTree{

    vector<ll>ST;
    ll N;
    SegmentTree(ll Size)
    {
        N = Size;

        ST.assign(4*N,0);
    }
    void update(ll i, ll v)
    {
        return update(1,0,N-1,i,v);
    }
    void update(ll n,ll l,ll r,ll i, ll v)
    {
        if(i < l || r < i) return;

        if(l==r)
        {
            ST[n] += v;
            return;
        }

        update(2*n,l,(l+r)/2,i,v);
        update(2*n+1,(l+r)/2+1,r,i,v);

        ST[n]=ST[2*n]+ST[2*n+1];
    }
    ll query(ll i,ll j)
    {
        return query(1,0,N-1,i,j);
    }
    ll query(ll n,ll l,ll r, ll i, ll j)
    {
        if(r < i || j < l)
        {
            return 0;
        }
        if(i <= l && r <= j)
        {
            return ST[n];
        }
        return query(2*n,l,(l+r)/2,i,j)+query(2*n+1,(l+r)/2+1,r,i,j);
    }
};
struct SegmenTree2D
{
    vector<SegmentTree>ST;
    ll N;
    SegmenTree2D(ll Size)
    {
        N = Size;

        ST.resize(4*N,Size);

    }

    void update(ll i,ll j, ll v)
    {
        return update(1,0,N-1,i,j,v);
    }
    void update(ll n,ll l,ll r,ll i,ll j, ll v)
    {
        if(i < l || r < i) return;

        if(l==r)
        {
            ST[n].update(j,v);
            return;
        }

        update(2*n,l,(l+r)/2,i,j,v);
        update(2*n+1,(l+r)/2+1,r,i,j,v);

        ST[n].update(j,v);
    }
    ll query(ll i1,ll i2,ll j1,ll j2)
    {
        return query(1,0,N-1,i1,i2,j1,j2);
    }
    ll query(ll n,ll l,ll r,ll i1,ll i2,ll j1,ll j2)
    {
        //cout<<l<<" "<<r<<" "<<ST[n].query(i2,j2)<<endl;
        if(l > j1 || i1 > r)
        {
            return 0;
        }
        if(i1 <= l && r <= j1)
        {
            return ST[n].query(i2,j2);
        }
        return query(2*n,l,(l+r)/2,i1,i2,j1,j2)+query(2*n+1,(l+r)/2+1,r,i1,i2,j1,j2);
    }
};
int main()
{
    ll q,n,x,y,l,b,r,t,a;
    SegmenTree2D ST(1025);
    while(cin>>q)
    {
        if(q==0)
        {
            cin>>n;
        }
        else if(q==1)
        {
            cin>>x>>y>>a;
            ST.update(x,y,a);
        }
        else if(q==2)
        {
            cin>>l>>b>>r>>t;
            cout<<ST.query(l,b,r,t)<<"\n";
        }
        else
        {
            break;
        }
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
