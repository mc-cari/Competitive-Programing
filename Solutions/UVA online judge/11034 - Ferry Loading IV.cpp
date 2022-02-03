#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=1975&mosmsg=Submission+received+with+ID+24592333


int main()
{

    int T;
    cin>>T;
    while(T--)
    {
        int n,t,m,a,times=0;
        string x;
        queue<int> left,right;
        cin>>n>>m;
        for(int i=0;i<m;i++)
        {
            cin>>a>>x;
            if(x=="left")left.push(a);
            else right.push(a);
        }

        bool pos=0;
        while(!left.empty()|!right.empty())
        {
            int cargo=n*100;
            if(pos==0)
            {
                while(!left.empty()&&cargo-left.front()>=0)
                {
                    cargo-=left.front();
                    left.pop();
                }
            }
            else
            {
                while(!right.empty()&&cargo-right.front()>=0)
                {
                    cargo-=right.front();
                    right.pop();
                }
            }
            pos=!pos;
            times++;

        }
        cout<<times<<"\n";
    }

}
