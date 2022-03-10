#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
/*
NO FUNCIONA EN URI
https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=260&page=show_problem&problem=1659
*/
#define INF 1e14
ll n,sellers;
vl ans;
vector<string>input;
vector<vector<vl> >com;
void backtrack(ll seller,vector<ll>& sol,ll last,ll sum)
{
    if(last>=input[seller].length())return;
    if(sol.size()==n)
    {
        if(input[seller].length()-last<=6&&input[seller].length()-last>0)
        {
            string s=input[seller].substr(last,input[seller].length()-last);
            if(s[0]=='0'&&s.length()!=1)return;
            ll t=stoi(s);
            if(sum==t)
            {
                sol.push_back(t);
                com[seller].push_back(sol);
                sol.pop_back();
            }
        }
    }
    if(sol.size()>=n)
        return;
    for(ll i=1;i<=4&&last+i-1<input[seller].length();i++)
    {
        string s=input[seller].substr(last,i);
        if(s[0]=='0'&&s.length()!=1)break;
        ll t=stoi(s);
        sol.push_back(t);
        backtrack(seller,sol,last+i,sum+t);
        sol.pop_back();
    }
    return;
}
bool o;
void backtrack2(ll seller,vl& sum,vl& sol)
{
    if(o)return;
    if(seller==sellers)
    {
        for(ll i=0;i<com[seller].size();i++)
        {
            if(sum==com[seller][i])
            {
                sol.push_back(i);
                o=1;
                ans.assign(sol.begin(),sol.end());
                break;
            }
        }


        return;
    }

    for(ll i=0;i<com[seller].size();i++)
    {
        for(ll j=0;j<n+1;j++)
        {
            sum[j]+=com[seller][i][j];
        }
        sol.push_back(i);
        backtrack2(seller+1,sum,sol);
        if(o)return;
        sol.pop_back();
        for(ll j=0;j<n+1;j++)
        {
            sum[j]-=com[seller][i][j];
        }
    }

}

int main()
{
    ll t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        n=0;sellers=0;
        input.clear();
        for(ll i=0;i<s.length();i++)
        {
            if(isdigit(s[i]))n=max(int(n),s[i]-'0');
        }
        while(1)
        {
            cin>>s;
            input.push_back(s);
            if(s[0]=='T'&&s[1]=='P'&&isdigit(s[2]))break;
            sellers++;
        }
        com.clear();
        com.assign(sellers+1,vector<vl>(0));
        vector<string>names;
        for(ll i=0;i<sellers+1;i++)
        {
            vl v;
            ll in=0;
            while(!isdigit(input[i][in]))
            {
                in++;
            }
            names.push_back(input[i].substr(0,in));
            backtrack(i,v,in,0);
        }
        ans.clear();
        vl v;
        o=0;
        vl sum(n+1,0);
        backtrack2(0,sum,v);
        for(ll i=1;i<=n;i++)
        {
            cout<<"P"<<i<<" ";
        }
        cout<<"Totals\n";
        for(ll i=0;i<ans.size();i++)
        {
            cout<<names[i];
            for(ll j=0;j<com[i][ans[i]].size();j++)
            {
                cout<<" "<<com[i][ans[i]][j];
            }
            cout<<'\n';
        }
    }
	return 0;
}
