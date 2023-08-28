#include "../Header.cpp"

struct SparseTable
{
    vector<vl >SP;
	
    SparseTable(vl&A)
    {
        int n = A.size();
        SP.push_back(A);
        ll maxlog = 31 - __builtin_clz(n);
        repx(i, 1 ,maxlog+1)
		{
			vl aux;
			rep(j, n-(1<<i)+1)
            {
                aux.push_back(max(SP[i-1][j],SP[i-1][j+(1<<(i-1))]));
            }
            SP.push_back(aux);
        }

    }
    ll op(int l, int r)
    {
        ll maxlog = 31 - __builtin_clz(r-l+1);
        return max(SP[maxlog][l],SP[maxlog][r-(1<<maxlog)+1]);
    }
    ll find(int l, int r, ll m) // maxi
    {
      ll maxlog = 31 - __builtin_clz(r-l+1);
      for(int i = maxlog; i >= 0; i--){
        if(l + (1<<i) <= r && SP[i][l] < m){
          l += (1<<i);
        }
      }
      return l;
    }
};
