#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=1842&mosmsg=Submission+received+with+ID+24592294


int main()
{

    int T;
    cin>>T;
    while(T--)
    {
        int n,t,m,a,time=0;
        string x;
        queue<pair<int,int> > left,right;
        cin>>n>>t>>m;
        for(int i=0;i<m;i++)
        {
            cin>>a>>x;
            if(x=="left")left.push(make_pair(a,i));
            else right.push(make_pair(a,i));
        }
        int d[m];
        bool pos=0;
        while(!left.empty()|!right.empty())
        {
            bool o=0;
            int cargo=n;
            if(pos==0)
            {
                while(!left.empty()&&cargo&&left.front().first<=time)
                {
                    d[left.front().second]=t+time;
                    o=1;
                    left.pop();
                    cargo--;
                }
                if(((!right.empty()&&!left.empty()&&right.front().first<left.front().first)||left.empty())&&!o){
                        o=1;
                        if(right.front().first>time)
                            time=right.front().first;
                }
                if(!o)time=left.front().first;
            }
            else
            {
                while(!right.empty()&&cargo&&right.front().first<=time)
                {
                    d[right.front().second]=time+t;
                    o=1;
                    right.pop();
                    cargo--;
                }
                if(((!right.empty()&&!left.empty()&&left.front().first<right.front().first)||right.empty())&&!o)
                {
                    o=1;
                    if(left.front().first>time)
                        time=left.front().first;
                }
                if(!o)time=right.front().first;
            }
            if(o)
            {
                pos=!pos;
                time+=t;
            }

        }
        for(int i=0;i<m;i++)
        {
            cout<<d[i]<<"\n";
        }
        if(T!=0)cout<<"\n";
    }

}
