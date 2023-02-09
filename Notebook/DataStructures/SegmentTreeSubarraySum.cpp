#include "../Header.cpp"

//https://www.geeksforgeeks.org/maximum-subarray-sum-given-range/
// Max subarray sum
struct Node
{
	//maxPrefixSum, maxSuffixSum, Totalsum, maxSubarraySum
	ll mxP, mxS, sum, subSum;
	Node()
	{
			mxP = mxS = sum = subSum = -INF;
	}
	Node merge(Node r)
	{
		Node p;
		p.mxP = max(mxP, sum + r.mxP);
		p.mxS = max(r.mxS, r.sum + mxS);
		p.sum = sum + r.sum;
		p.subSum = max({subSum, r.subSum, mxS + r.mxP});
		return p;
	}
	void upd(ll v)
	{
		mxP = mxS = sum = subSum = v;
	}
	void nul()
	{
			mxP = mxS = subSum = -INF;
			sum = 0;
	}
};


// Node version
struct SegmentTree
{
	vector<Node> ST;
	int N;
	SegmentTree(vl &A)
	{
		N = A.size();
		ST.assign(4*N, Node());
		bd(1,0,N-1,A);
	}
	void bd(int n, int l, int r, vl &A)
	{
		if(l == r)
		{
			ST[n].upd(A[l]);
			return;
		}

		bd(2*n,l,(l+r)/2,A);
		bd(2*n+1,(l+r)/2+1,r,A);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
	Node qry(int i, int j)
	{
		return qry(1,0,N-1,i,j);
	}
	Node qry(int n, int l, int r, int i, int j)
	{

		if(r < i || j < l) 
		{
				Node p;
				p.nul();
				return p;
		}

		if(i <= l && r <= j) return ST[n];

		return qry(2*n,l,(l+r)/2,i,j).merge(qry(2*n+1,(l+r)/2+1,r,i,j));
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
			ST[n].upd(v);
			return;
		}
		upd(2*n,l,(l+r)/2,i,v);
		upd(2*n+1,(l+r)/2+1,r,i,v);

		ST[n] = ST[2*n].merge(ST[2*n+1]);
	}
};