#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=676
int main()
{
    int n;
    while(cin>>n)
    {
        if(n<=0)break;
        vl c;
        for(int i=0;i<=20;i++)
        {
            for(int j=1;j<=3;j++)
                c.push_back(i*j);
        }
        c.push_back(50);
        sort(ALL(c));
        UNIQUE(c);
        ll comb=0,perm=0;
        for(int i=0;i<c.size();i++)
            for(int j=0;j<c.size();j++)
                for(int z=0;z<c.size();z++)
                    if(c[i]+c[j]+c[z]==n)perm++;
        for(int i=0;i<c.size();i++)
            for(int j=i;j<c.size();j++)
                for(int z=j;z<c.size();z++)
                    if(c[i]+c[j]+c[z]==n)comb++;
        if(comb==0)
        {
            cout<<"THE SCORE OF "<<n<<" CANNOT BE MADE WITH THREE DARTS.\n";
        }
        else
        {
            cout<<"NUMBER OF COMBINATIONS THAT SCORES "<<n<<" IS "<<comb<<".\n";
            cout<<"NUMBER OF PERMUTATIONS THAT SCORES "<<n<<" IS "<<perm<<".\n";
        }
        cout<<"**********************************************************************\n";
    }
    cout<<"END OF OUTPUT\n";
}
