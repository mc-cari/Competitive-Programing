#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SparseTable
{
    vector<vl >SP;
    SparseTable(vl&A)
    {
        int n=A.size();
        SP.push_back(A);
        int maxlog = 31 - __builtin_clz(n);
        for(int i=1;i<=maxlog;i++)
        {
            vl c;
            for(int j=0;j<n-(1<<i)+1;j++)
            {
                c.push_back(min(SP[i-1][j],SP[i-1][j+(1<<(i-1))]));
            }
            SP.push_back(c);
        }
        /*for(int i=0;i<=maxlog;i++)
        {
            for(int j=0;j<n-(1<<i)+1;j++)
            {
                cout<<SP[i][j]<<" ";
            }
            cout<<endl;
        }*/
    }
    int op(int l,int r)
    {
        //cambiar operaci�n arriba
        int maxlog = 31 - __builtin_clz(r-l+1);
        return min(SP[maxlog][l],SP[maxlog][r-(1<<maxlog)+1]);
    }
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll n,m,x,y,h,v;

    vector<int>A = {7,10,19,3,1,2,7,7};
    SparseTable SP(A);
    cout<<SP.op(1,3)<<endl;




    return 0;
}
