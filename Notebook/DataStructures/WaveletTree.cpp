#include "../Header.cpp"
typedef vector<int>::iterator iter;

//Wavelet tree with succinct representation of bitmaps
struct WaveTreeSucc {
  vector<vector<int> > C; int s;

  // sigma = size of the alphabet, ie., one more than the maximum element
  // in S.
  // si no  esta indexado desde 0, agregar mas tamaño(sigma)

  

  WaveTreeSucc(vector<int> &A, int sigma) : C(sigma*2), s(sigma) {
    build(A.begin(), A.end(), 0, s-1, 1);
  }

  void build(iter b, iter e, int L, int U, int u) {
    if (L == U)
      return;
    int M = (L+U)/2;

    // C[u][i] contains number of zeros until position i-1: [0,i)
    C[u].reserve(e-b+1); C[u].push_back(0);
    for (iter it = b; it != e; ++it)
      C[u].push_back(C[u].back() + (*it<=M));

    iter p = stable_partition(b, e, [=](int i){return i<=M;});

    build(b, p, L, M, u*2);
    build(p, e, M+1, U, u*2+1);
  }

  // Count occurrences of number c until position i.
  // ie, occurrences of c in positions [i,j]
  int rank(int c, int i) const {
    // Internally we consider an interval open on the left: [0, i)
    i++;
    int L = 0, U = s-1, u = 1, M, r;
    while (L != U) {
      M = (L+U)/2;
      r = C[u][i]; u*=2;
      if (c <= M)
        i = r, U = M;
      else
        i -= r, L = M+1, ++u;
    }
    return i;
  }

  // Find the k-th smallest element in positions [i,j].
  // The smallest element is k=1
  int quantile(int k, int i, int j) const {
    // internally we we consider an interval open on the left:  [i, j)
    j++;
    int L = 0, U = s-1, u = 1, M, ri, rj;
    while (L != U) {
      M = (L+U)/2;
      ri = C[u][i]; rj = C[u][j]; u*=2;
      if (k <= rj-ri)
        i = ri, j = rj, U = M;
      else
        k -= rj-ri, i -= ri, j -= rj,
          L = M+1, ++u;
    }
    return U;
  }

  // Count number of occurrences of numbers in the range [a, b]
  // present in the sequence in positions [i, j], ie, if representing a grid it
  // counts number of points in the specified rectangle.
  mutable int L, U;
  int range(int i, int j, int a, int b) const {
    if (b < a or j < i)
      return 0;
    L = a; U = b;
    return range(i, j+1, 0, s-1, 1);
  }

  int range(int i, int j, int a, int b, int u) const {
    if (b < L or U < a)
      return 0;
    if (L <= a and b <= U)
      return j-i;
    int M = (a+b)/2, ri = C[u][i], rj = C[u][j];
    return range(ri, rj, a, M, u*2) +
      range(i-ri, j-rj, M+1, b, u*2+1);
  }
};

//https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/master/data_structures/wavelet_tree_test.cpp
struct WT {
	vector<int> wt[1<<20];int n;
	void init(int k, int s, int e){
		if(s+1==e)return;
		wt[k].clear();wt[k].pb(0);
		int m=(s+e)/2;
		init(2*k,s,m);init(2*k+1,m,e);
	}
	void add(int k, int s, int e, int v){
		if(s+1==e)return;
		int m=(s+e)/2;
		if(v<m)wt[k].pb(wt[k].back()),add(2*k,s,m,v);
		else wt[k].pb(wt[k].back()+1),add(2*k+1,m,e,v);
	}
	int query0(int k, int s, int e, int a, int b, int i){
		if(s+1==e)return s;
		int m=(s+e)/2;
		int q=(b-a)-(wt[k][b]-wt[k][a]);
		if(i<q)return query0(2*k,s,m,a-wt[k][a],b-wt[k][b],i);
		else return query0(2*k+1,m,e,wt[k][a],wt[k][b],i-q);
	}
	void upd(int k, int s, int e, int i){
		if(s+1==e)return;
		int m=(s+e)/2;
		int v0=wt[k][i+1]-wt[k][i],v1=wt[k][i+2]-wt[k][i+1];
		if(!v0&&!v1)upd(2*k,s,m,i-wt[k][i]);
		else if(v0&&v1)upd(2*k+1,m,e,wt[k][i]);
		else if(v0)wt[k][i+1]--;
		else wt[k][i+1]++;
	}
	void init(int _n){n=_n;init(1,0,n);} // (values in range [0,n))
	void add(int v){add(1,0,n,v);}
	int query0(int a, int b, int i){ // ith element in range [a,b)
		return query0(1,0,n,a,b,i);    // (if it was sorted)
	}
	void upd(int i){ // swap positions i,i+1
		upd(1,0,n,i);
	}
};
