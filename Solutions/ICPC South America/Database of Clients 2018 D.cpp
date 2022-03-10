#include<bits/stdc++.h>
using namespace std;
urionlinejudge.com.br/judge/es/problems/view/2906
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int n,sum=0;
    string x;
    map<string,set<string> >p;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        bool per=1;
        string persona="",provider="";
        for(int j=0;j<x.length();j++)
        {
            if(x[j]=='@'||x[j]=='+')per=0;
            if(x[j]=='@')
            {
                provider=x.substr(j+1,x.length()-j+1);
                break;
            }
            if(per)
            {
                if(x[j]!='.')
                    persona+=x[j];
            }
        }
        if(!p[provider].count(persona))
        {
            p[provider].insert(persona);
            sum++;
        }
    }
    cout<<sum<<"\n";
	return 0;
}
