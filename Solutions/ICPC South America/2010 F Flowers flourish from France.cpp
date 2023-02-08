#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1140
#define INF 1e14
int main()
{
    string s;
    while(getline(cin,s))
    {
        if(s=="*")break;
        int in=0;
        vector<string>c;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]==' ')
            {
                c.push_back(s.substr(in,i-in));
                in=i+1;
            }
        }
        c.push_back(s.substr(in,s.length()-in));
        set<char>d;
        for(string i : c)
        {
            d.insert(tolower(i[0]));
        }
        if(d.size()==1)
        {
            cout<<"Y\n";
        }
        else cout<<"N\n";
    }
}
