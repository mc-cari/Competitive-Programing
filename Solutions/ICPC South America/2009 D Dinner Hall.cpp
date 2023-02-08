#include<bits/stdc++.h>
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    int n,x;
    while(cin>>n)
    {
        if(n==0)break;
        int t=0,E=0,X=0,res=0;
        char x;
        string s;
        vector<tuple<int,int,int,char> >c;
        for (int i=0;i<n;i++)
        {
            cin>>s>>x;
            if(x=='?')t++;
            else if(x=='E')E++;
            else X++;
            c.push_back(make_tuple(stoi(s.substr(0,2)),stoi(s.substr(3,2)),stoi(s.substr(6,2)),x));
        }
        if(X>E)
        {
            res+=X-E;
            t-=X-E;
        }
        else if(E>X)
        {
            t-=E-X;
        }
        res+=t/2;
        int sum=0,maxi=-1;;
        sort(c.begin(),c.end());
        for(int i=0;i<n;i++)
        {
            if(get<3>(c[i])=='?')
            {
                if(res)
                {
                    res--;
                    get<3>(c[i])='E';
                }
                else get<3>(c[i])='X';
            }
            if(get<3>(c[i])=='E')
            {
                sum++;
            }
            else sum--;
            if(sum>maxi)maxi=sum;
        }
        cout<<maxi<<"\n";
    }
}
