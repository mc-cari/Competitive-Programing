#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=549
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        vector<string>a,b,c;
        string x,y,z;
        int even=0;
        cin>>x>>y>>z;
        a.push_back(x);
        b.push_back(y);
        c.push_back(z);
        if(z=="even")even++;
        cin>>x>>y>>z;
        a.push_back(x);
        b.push_back(y);
        c.push_back(z);
        if(z=="even")even++;
        cin>>x>>y>>z;
        a.push_back(x);
        b.push_back(y);
        c.push_back(z);
        vl vis(28,0),cont(28,0),cont2(28,0);
        string ans;
        bool o=1;
        if(z=="even")even++;
        if(even==2)
        {
            int in;
            for(int i=0;i<3;i++)
            {
                if(c[i]!="even")in=i;
                else
                {
                    for(int j=0;j<a[i].length();j++)
                    {
                        vis[a[i][j]-'A']=1;
                    }
                    for(int j=0;j<b[i].length();j++)
                    {
                        vis[b[i][j]-'A']=1;
                    }
                }
            }
            for(int j=0;j<a[in].length();j++)
            {
                if(!vis[a[in][j]-'A']){
                    ans=a[in][j];
                    if(c[in]=="up")o=0;
                    else o=1;
                }
            }
            for(int j=0;j<b[in].length();j++)
            {
                if(!vis[b[in][j]-'A']){
                    ans=b[in][j];
                    if(c[in]=="up")o=1;
                    else o=0;

                }
            }
            if(o)
                cout<<ans<<" is the counterfeit coin and it is light.\n";
            else
                cout<<ans<<" is the counterfeit coin and it is heavy.\n";
        }
        else if(even==1)
        {
            int in;
            for(int i=0;i<3;i++)
            {
                if(c[i]=="even")
                {
                    for(int j=0;j<a[i].length();j++)
                    {
                        vis[a[i][j]-'A']=1;
                    }
                    for(int j=0;j<b[i].length();j++)
                    {
                        vis[b[i][j]-'A']=1;
                    }
                }
            }
            ans=" ";
            for(int i=0;i<3;i++)
            {
                if(c[i]=="up")
                {
                    for(int j=0;j<b[i].length();j++)
                    {
                        if(vis[b[i][j]-'A'])continue;
                        cont[b[i][j]-'A']++;
                    }
                    for(int j=0;j<a[i].length();j++)
                    {
                        if(vis[a[i][j]-'A'])continue;
                        cont2[a[i][j]-'A']++;
                    }
                }
                else if(c[i]=="down")
                {
                    for(int j=0;j<b[i].length();j++)
                    {
                        if(vis[b[i][j]-'A'])continue;
                        cont2[b[i][j]-'A']++;
                    }
                    for(int j=0;j<a[i].length();j++)
                    {
                        if(vis[a[i][j]-'A'])continue;
                        cont[a[i][j]-'A']++;
                    }
                }
            }
            int co=0;
            for(int i=0;i<28;i++)
            {
                if(cont[i]==2)
                {
                    o=1;
                    co++;
                    ans=char(i+'A');
                }
            }
            if(co!=1)
            {

                for(int i=0;i<28;i++)
                {
                    if(cont2[i]==2)
                    {
                        o=0;
                        co++;
                        ans=char(i+'A');
                    }
                }
            }
            if(o)
                cout<<ans<<" is the counterfeit coin and it is light.\n";
            else
                cout<<ans<<" is the counterfeit coin and it is heavy.\n";
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                if(c[i]=="up")
                {
                    for(int j=0;j<b[i].length();j++)
                    {
                        if(vis[b[i][j]-'A'])continue;
                        cont[b[i][j]-'A']++;
                    }
                    for(int j=0;j<a[i].length();j++)
                    {
                        if(vis[a[i][j]-'A'])continue;
                        cont2[a[i][j]-'A']++;
                    }
                }
                else if(c[i]=="down")
                {
                    for(int j=0;j<b[i].length();j++)
                    {
                        if(vis[b[i][j]-'A'])continue;
                        cont2[b[i][j]-'A']++;
                    }
                    for(int j=0;j<a[i].length();j++)
                    {
                        if(vis[a[i][j]-'A'])continue;
                        cont[a[i][j]-'A']++;
                    }
                }
            }
            int co=0;
            for(int i=0;i<28;i++)
            {
                if(cont[i]==3)
                {
                    co++;
                    o=1;
                    ans=char(i+'A');
                }
            }
            if(co!=1)
            {

                for(int i=0;i<28;i++)
                {
                    if(cont2[i]==3)
                    {
                        co++;
                        ans=char(i+'A');
                        o=0;
                    }
                }
            }
            if(o)
                cout<<ans<<" is the counterfeit coin and it is light.\n";
            else
                cout<<ans<<" is the counterfeit coin and it is heavy.\n";
        }

    }
}
