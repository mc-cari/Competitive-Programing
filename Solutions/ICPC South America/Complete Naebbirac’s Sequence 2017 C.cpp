#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/2697
int main()
{
    int k,n,x,r=0,R;cin>>k>>n;
    map<int,int>m;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        m[x]++;
        if(x<1||x>k)
        {
            R=x;
            r++;
        }
    }
    if(r>1)
    {
        cout<<"*\n";
        return 0;
    }
    vector<pll>c;
    for(int i=1;i<=k;i++)
    {
        c.push_back(make_pair(m[i],i));
    }
    sort(c.begin(),c.end());
    if(r==1)
    {
        bool o=0;
        for(int i=1;i<c.size();i++)
        {
            if(c[0].first!=c[i].first)
            {
                o=1;
                break;
            }
        }
        if(o==1)
        {
            c[0].first++;
            o=0;
            for(int i=1;i<c.size();i++)
            {
                if(c[0].first!=c[i].first)
                {
                    o=1;
                    break;
                }
            }
            if(o)
            {
                cout<<"*\n";
                return 0;

            }
            else
            {
                cout<<"-"<<R<<" +"<<c[0].second<<"\n";
            }
        }
        else
        {
            cout<<"-"<<R<<"\n";
        }
    }
    else
    {
        c[0].first++;
        bool o=0;
        for(int i=1;i<c.size();i++)
        {
            if(c[0].first!=c[i].first)
            {
                o=1;
                break;
            }
        }
        if(!o)
        {
            cout<<"+"<<c[0].second<<"\n";
            return 0;
        }
        o=0;
        c[c.size()-1].first--;
        for(int i=0;i<c.size()-1;i++)
        {
            if(c[c.size()-1].first!=c[i].first)
            {
                o=1;
                break;
            }
        }
        if(!o)
        {
            cout<<"-"<<c[c.size()-1].second<<" +"<<c[0].second<<"\n";
            return 0;
        }
        o=0;
        c[0].first--;
        for(int i=0;i<c.size()-1;i++)
        {
            if(c[c.size()-1].first!=c[i].first)
            {
                o=1;
                break;
            }
        }
        if(!o)
        {
            cout<<"-"<<c[c.size()-1].second<<"\n";
            return 0;
        }
        cout<<"*\n";
        return 0;
    }

}
