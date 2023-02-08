#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=2261&mosmsg=Submission+received+with+ID+24610992
int main() {
    int n;
    while(cin>>n)
    {
        if(n==0)break;
        vector<set<int> >c;
        map<set<int>,int>d;
        set<int>x;
        int y,maxi=-1,sum=0;
        for(int i=0;i<n;i++)
        {
            x.clear();
            for(int j=0;j<5;j++)
            {
                cin>>y;
                x.insert(y);
            }
            c.push_back(x);
            d[x]++;
            if(d[x]>maxi)maxi=d[x];
        }
        for(int i=0;i<n;i++)
        {
            if(maxi==d[c[i]])
            {
                sum++;
            }
        }
        cout<<sum<<"\n";
    }


}
