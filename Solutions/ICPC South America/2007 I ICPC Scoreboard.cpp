#include<bits/stdc++.h>
using namespace std;
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1936
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8

bool o;
bool sor(pll& x, pll& y )
{
    if(x.first+x.second*20==y.first+y.second*20&&x.first!=y.first&&x.second!=y.second)
    {
        o=1;
    }
    if(x.first+x.second*20<y.first+y.second*20)
    {
        return 1;
    }return 0;
}
bool ver(ll mul,vector<pll>& c)
{
    for(ll i=0;i<c.size()-1;i++)
    {
        //cout<<c[i].first+c[i].second*mul<<" "<<c[i+1].first+c[i+1].second*mul<<endl;
        if(c[i].first+c[i].second*20==c[i+1].first+c[i+1].second*20)
        {
            continue;
        }
        if(c[i].first+c[i].second*mul>=c[i+1].first+c[i+1].second*mul)
            return 0;
    }
    return 1;
}
int main()
{

    ll t,p;
    while(cin>>t>>p)
    {
        if(t+p==0)break;
        o=0;
        vector<vector<pll> >c(p+1,vector<pll>(0));
        for(ll i=0;i<t;i++)
        {
            ll acumbase=0,mul=0,problems=0;
            for(ll j=0;j<p;j++)
            {
                string x;
                ll pos=0,a,b;
                cin>>x;
                if(x[x.length()-1]=='-')continue;
                for(ll z=0;z<x.length();z++)
                {
                    if(x[z]=='/')
                    {
                        pos=z;
                        break;
                    }
                }
                a=stoi(x.substr(0,pos));
                b=stoi(x.substr(pos+1,x.length()-pos-1));
                acumbase+=b;
                mul+=a-1;
                problems++;
            }
            c[problems].push_back(make_pair(acumbase,mul));
        }
        for(ll i=0;i<=p;i++)
        {
            sort(c[i].begin(),c[i].end(),sor);
        }
        if(o)
        {
            o=0;
            cout<<"20 20\n";
            continue;
        }
        ll left=1,right=INF;
        for(ll i=1;i<=p;i++)
        {
            if(c[i].size()<2)continue;
            /*cout<<i<<"::\n";
            for(ll j=0;j<c[i].size();j++){
                cout<<c[i][j].first<<" "<<c[i][j].second<<endl;
            }*/
            ll l=20,r=INF,P;
            while(l<=r)
            {
                P=(l+r)/2;
                //cout<<P<<"->\n";
                if(ver(P,c[i]))l=P+1;
                else r=P-1;
            }
            right=min(right,r);
            l=20;
            while(l-1>=1&&ver(l-1,c[i]))
            {
                l--;
            }
            left=max(left,l);
        }
        if(right<5000000)
        cout<<left<<" "<<right<<"\n";
        else
            cout<<left<<" *\n";
    }


    return 0;
}
