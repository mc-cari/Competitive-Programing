#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2041
int main()
{
    int n,cop=0;
    while(cin>>n)
    {
        if(n==0)break;
        if(cop!=0)cout<<"\n";
        cop++;
        int x,maxi=-1;;
        map<int,int>m;
        vl c;

        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
            m[x]++;
            if(m[x]>maxi)maxi=m[x];
        }
        sort(ALL(c));
        vector<vl>ans(maxi,vl(0));
        for(int i=0;i<n;i++)
        {
            ans[i%maxi].push_back(c[i]);
        }
        cout<<maxi<<"\n";
        for(int i=0;i<ans.size();i++)
        {
            for(int j=0;j<ans[i].size();j++)
            {
                cout<<ans[i][j];
                j<ans[i].size()-1 ? cout<<" ":cout<<"\n";
            }
        }


    }
}
