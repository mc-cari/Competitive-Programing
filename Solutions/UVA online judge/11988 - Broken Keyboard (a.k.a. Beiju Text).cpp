#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=3139&mosmsg=Submission+received+with+ID+24586255

int main()
{
    string s;
    while(getline(cin,s))
    {
        list<char>c;
        list<char>:: iterator it;
        it=c.begin();
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='[')
            {
                it=c.begin();
            }
            else if(s[i]==']')
            {
                it=c.end();
            }
            else
            {
                c.insert(it,s[i]);
            }
        }
        for( auto i : c)
        {
            cout<<i;
        }cout<<"\n";
    }
}
