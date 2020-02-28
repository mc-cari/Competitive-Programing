#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2176
struct SegmentTree
{
	vl ST;
	ll N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.resize(4*N);
		build(1,0,N-1,A);
	}

	void build(ll n, ll l, ll r, vl &A)
	{
		if(l==r)
		{
			ST[n]=A[r];
			return;
		}

		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);
		ST[n] = max(ST[2*n],ST[2*n+1]);

	}

	ll query(ll i, ll j)
	{
		return query(1,0,N-1,i,j);
	}

	ll query(ll n, ll l, ll r, ll i, ll j)
	{

		if(r < i || j < l) return 0;


		if(i <= l && r <= j) return ST[n];

		return max(query(2*n,l,(l+r)/2,i,j),query(2*n+1,(l+r)/2+1,r,i,j));
	}

};

int main()
{
	int n,q;
	while(cin>>n)
    {
        if(n==0)break;
        cin>>q;
        vl c,m;
        vector<pair<int,int> > A;
        map<int,int>d;
        int x,in=0,prev=0;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);

            if(i>0&&c[i]!=c[i-1])
            {
                in++;

                A.push_back(make_pair(prev+1,i));
                m.push_back(i-prev);
                prev=i;
            }
            d[x]=in;
        }
        A.push_back(make_pair(prev+1,n));
        m.push_back(n-prev);
        SegmentTree ST(m);
        while(q--)
        {
            int x,y;
            cin>>x>>y;
            if(d[c[x-1]]==d[c[y-1]])
            {
                cout<<y-x+1<<"\n";
            }
            else
            {
                int maxi=-1;
                maxi=max(A[d[c[x-1]]].second-x+1,y-A[d[c[y-1]]].first+1);
                if(d[c[x-1]]+1!=d[c[y-1]])
                {
                    maxi=max((ll)maxi,ST.query(d[c[x-1]]+1,d[c[y-1]]-1));
                }
                cout<<maxi<<"\n";
            }

        }


    }
	return 0;
}
