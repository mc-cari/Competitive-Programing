#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=1508&mosmsg=Submission+received+with+ID+24653859
int main()
{

    string s,y;
    int q,x;
    vector<vector<int> >c(52,vector<int>(0));
    cin>>s;
    map<char,int>k;
    for(int i=0;i<='Z'-'A';i++)
    {
        k[char(i+'A')]=i;
    }
    for(int i=0;i<='z'-'a';i++)
    {
        k[char(i+'a')]=i+26;
    }
    for(int i=0;i<s.size();i++)
    {
        c[k[s[i]]].push_back(i);
    }
    cin>>q;
    while(q--)
    {
        cin>>y;
        bool o=1;
        int in=0,sol1=-1,sol2;
        vl prev(52,0);
        for(int i=0;i<y.size();i++)
        {

            int res=-1,l=prev[k[y[i]]],r=c[k[y[i]]].size()-1,p;
            while(l<=r)
            {
                p=(r+l)/2;
                if(c[k[y[i]]][p]>=in)
                {
                    res=c[k[y[i]]][p];
                    prev[k[y[i]]]=p+1;
                    r=p-1;
                }
                else l=p+1;
            }
            if(res==-1)
            {
                o=0;
                break;
            }
            else
            {
                in=res+1;
            }
            if(i==0)sol1=in-1;
            if(i==y.size()-1)sol2=in-1;
        }
        if(o)
        {
            cout<<"Matched "<<sol1<<" "<<sol2<<"\n";
        }
        else
            cout<<"Not matched\n";
    }
}
