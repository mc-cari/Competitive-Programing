#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://www.urionlinejudge.com.br/judge/es/problems/view/1301
struct SegmentTree
{
	vector<int> ST;
	int N;

	SegmentTree(vl &A)
	{
		N = A.size();
		ST.resize(4*N);
		build(1,0,N-1,A);
	}

	void build(int n, int l, int r, vl &A)
	{
		if(l==r)
		{
			ST[n]=A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		ST[n] = ST[2*n]*ST[2*n+1];
	}

	int query(int i, int j)
	{
		return query(1,0,N-1,i,j);
	}

	int query(int n, int l, int r, int i, int j)
	{

		if(r < i || j < l) return 1;


		if(i <= l && r <= j) return ST[n];

		return (query(2*n,l,(l+r)/2,i,j)*query(2*n+1,(l+r)/2+1,r,i,j));
	}

	void update(int i, int v)
	{
		return update(1,0,N-1,i,v);
	}

	void update(int n, int l, int r, int i, int v)
	{

		if(i < l || r < i) return;

		if(l == r)
		{
			ST[n] = v;
			return;
		}

		update(2*n,l,(l+r)/2,i,v);
		update(2*n+1,(l+r)/2+1,r,i,v);

		ST[n] = ST[2*n]*ST[2*n+1];
	}
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k,x;
    while(cin>>n>>k){
        vl c;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(x==0)
                c.push_back(x);
            else
                c.push_back(x/abs(x));
        }
        SegmentTree ST(c);
        char a;int y;
        for(int i=0;i<k;i++)
        {
            cin>>a;
            if(a=='C')
            {
                cin>>x>>y;
                if(y==0)
                {
                    ST.update(x-1,0);
                }
                else
                    ST.update(x-1,y/abs(y));
            }
            else
            {
                cin>>x>>y;
                int q=ST.query(x-1,y-1);
                if(q==0)
                {
                    cout<<0;
                }
                else if(q>0)
                {
                    cout<<"+";
                }
                else
                {
                    cout<<"-";
                }
            }
        }
        cout<<"\n";
    }
}
