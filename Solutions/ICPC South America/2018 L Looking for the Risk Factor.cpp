#include<bits/stdc++.h>
#include<vector>
#include<algorithm>
//#include "bitmap.hpp"
//https://www.urionlinejudge.com.br/judge/es/problems/view/2914
using namespace std;

vector <bool> crib;
long long criba(long long b)
{
    crib.assign(b,true);
    crib[0]=false;
    crib[1]=false;
    for(int k=2;k<sqrt(b+1)+1;k++)
    {
        if(crib[k]==true)
        {
            for(int j=2;(j*k)<b+1;j++)//para optimizar j=k
            {
                crib[k*j]=false;
            }
        }
    }
}

typedef vector<int>::iterator iter;

//Wavelet tree with succinct representation of bitmaps
struct WaveTreeSucc {
  vector<vector<int> > C; int s;

  // sigma = size of the alphabet, ie., one more than the maximum element
  // in S.
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


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    criba(100005);
    vector<int>B(100004,0);
    vector<int>M(100004,0);
    int sum=0,in=0;
    B[0]=2;
    B[1]=2;
    for(int i=2;i<=100000;i++)
    {
        if(crib[i])
        {
            sum++;
            for(int j=i;j<=100000;j+=i)
            {
                B[j]=sum;
                in++;
            }
        }
        M[i]=sum;
    }
    WaveTreeSucc AC(B,sum);
    int q,n,k;
    cin>>q;
    while(q--)
    {
        cin>>n>>k;
        cout<<AC.range(2,n,1,M[k])<<"\n";
    }
    return 0;
}
