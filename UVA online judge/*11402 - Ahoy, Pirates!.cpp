#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2397
struct SegmentTree
{
	vector<ll> ST,Lazy;
	ll N;
    ll Nul = 0;
	SegmentTree(vector<ll> &A)
	{
		N = A.size();
		ST.resize(4*N+5,0);
		Lazy.resize(4*N+5,Nul);

		build(1,0,N-1,A);
	}
    void up(ll n, ll l, ll r)
    {
        int aux=Lazy[n];
        if(Lazy[n]==1)
        {
            ST[n]=r-l+1;
        }
        else if(Lazy[n]==-1)
        {
            ST[n]=0;
        }
        else if(Lazy[n]==2)
        {
            ST[n]=r-l+1-ST[n];
        }
        if(l!=r&&Lazy[n]!=0)
        {
            if(aux==2)
            {
                if(Lazy[n*2]==2)
                    Lazy[n*2]=0;
                else if(Lazy[n*2]==0)Lazy[n*2]=2;
                else Lazy[n*2]=-Lazy[n*2];
                if(Lazy[n*2+1]==2)
                    Lazy[n*2+1]=0;
                else if(Lazy[n*2+1]==0)Lazy[n*2+1]=2;
                else Lazy[n*2+1]=-Lazy[n*2+1];
            }
            else
            {
                Lazy[n*2] = aux;
                Lazy[n*2+1] = aux;
            }

        }
        Lazy[n] = Nul;
    }
	void build(ll n, ll l, ll r, vector<ll> &A)
	{

		if(l == r)
		{
			ST[n] = A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);


		ST[n] = (ST[2*n]+ST[2*n+1]);
	}

	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}


	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l ) return 0;

        if(Lazy[n]!=0)up(n,l,r);


		if(i <= l && r <= j) return ST[n];


		return query(2*n,l,(l+r)/2,i,j)+query(2*n+1,(l+r)/2+1,r,i,j);
	}

	void update(ll i,ll j, ll op)
	{
		return update(1,0,N-1,i,j, op);

	}

	void update(ll n, ll l, ll r, ll i, ll j,ll op)
	{

		if(l > j || r < i)
        {
            up(n,l,r);
            return;
        }
        if(i<=l&&r<=j)
        {
            up(n,l,r);
            Lazy[n]=op;
            up(n,l,r);
            return;
        }
        up(n,l,r);

		update(2*n,l,(l+r)/2,i,j,op);
		update(2*n+1,(l+r)/2+1,r,i,j,op);
		ST[n] = (ST[2*n]+ST[2*n+1]);
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll x,y,u,q,t,v;
	cin>>t;
	for(int k=1;k<=t;k++){
        string z="";
        int m;
        cin>>m;
        while(m--)
        {
            int xy;
            string s;
            cin>>xy>>s;
            while(xy--)
            {
                z+=s;
            }
        }
        vl A;
        for(int i=0;i<z.size();i++)
        {
            A.push_back(z[i]-'0');
        }
        SegmentTree ST(A);
        ll Q=1;
        cout<<"Case "<<k<<":\n";
        cin>>q;
        while(q--)
        {
            int a,b;
            char c;
            cin>>c>>a>>b;
            if(c=='F')
            {
                ST.update(a,b,1);
            }
            else if(c=='E')
            {
                ST.update(a,b,-1);
            }
            else if(c=='I')
            {
                ST.update(a,b,2);
            }
            else
            {
                cout<<"Q"<<Q<<": "<<ST.query(a,b)<<"\n";
                /*for(int i=0;i<=10;i++)
                {
                    cout<<ST.query(i,i)<<"-\n";
                }*/
                Q++;
            }
        }
	}

    return 0;
}
