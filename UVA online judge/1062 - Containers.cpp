#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3503&mosmsg=Submission+received+with+ID+24591469

int main()
{

    string s;
    int t=1;
    while(cin>>s)
    {
        if(s=="end")break;
        vector<stack<char> >c;
        stack<char>d;
        ll ans=0;
        for(int i=0;i<s.size();i++)
        {

            bool o=1;
            for(int j=0;j<c.size();j++)
            {
                if(c[j].top()>=s[i])
                {
                    c[j].push(s[i]);
                    o=0;
                    break;
                }
            }
            if(o)
            {
                d.push(s[i]);
                c.push_back(d);
                d.pop();
                ans++;
            }
        }
        cout<<"Case "<<t<<": "<<ans<<"\n";
        t++;

    }

}
