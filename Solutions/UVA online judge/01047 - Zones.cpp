#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3488
int main()
{
    int n,p,T=1;
    while(cin>>n>>p)
    {
        if(n+p==0)break;
        int x;
        vl c,perm;
        for(int i=0;i<n;i++)
        {
            if(p>0)perm.push_back(0);
            else perm.push_back(1);
            p--;
        }
        set<int>d;
        vector< pair<set<int>,int> >cov;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        int m;
        cin>>m;
        while(m--)
        {
            int t;
            cin>>t;
            d.clear();
            for(int i=0;i<t;i++)
            {
                cin>>x;
                d.insert(x);
            }
            cin>>x;
            cov.push_back(make_pair(d,x));
        }
        int maxi=-1;
        vl ans;
        do
        {
            vl aux;int sum=0;
            vl vis(cov.size(),0);
            for(int i=0;i<perm.size();i++)
            {
                if(perm[i]==0)
                {
                    aux.push_back(i);
                    sum+=c[i];
                    for(int j=0;j<cov.size();j++)
                    {
                        if(cov[j].first.count(i+1))
                        {
                            if(!vis[j])vis[j]=1;
                            else sum-=cov[j].second;
                        }
                    }
                }
            }
            if(sum>maxi)
            {
                maxi=sum;
                ans.clear();
                ans.assign(ALL(aux));
            }

        }while(next_permutation(ALL(perm)));
        cout<<"Case Number  "<<T<<"\n";
        cout<<"Number of Customers: "<<maxi<<"\n";
        cout<<"Locations recommended: ";
        for(int i=0;i<ans.size();i++)
        {
            cout<<ans[i]+1;
            i<ans.size()-1 ? cout<<" " : cout<<"\n";
        }
        cout<<"\n";
        T++;
    }
}
