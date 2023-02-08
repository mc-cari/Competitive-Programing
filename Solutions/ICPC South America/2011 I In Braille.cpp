#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1357
map<pair<int,int>,string>  m;



map<vector<string>,int>n;
vector<string>c;



int main()
{
    m[make_pair(1,0)]="*.";
    m[make_pair(1,1)]="..";
    m[make_pair(1,2)]="..";
    m[make_pair(2,0)]="*.";
    m[make_pair(2,1)]="*.";
    m[make_pair(2,2)]="..";
    m[make_pair(3,0)]="**";
    m[make_pair(3,1)]="..";
    m[make_pair(3,2)]="..";
    m[make_pair(4,0)]="**";
    m[make_pair(4,1)]=".*";
    m[make_pair(4,2)]="..";
    m[make_pair(5,0)]="*.";
    m[make_pair(5,1)]=".*";
    m[make_pair(5,2)]="..";
    m[make_pair(6,0)]="**";
    m[make_pair(6,1)]="*.";
    m[make_pair(6,2)]="..";
    m[make_pair(7,0)]="**";
    m[make_pair(7,1)]="**";
    m[make_pair(7,2)]="..";
    m[make_pair(8,0)]="*.";
    m[make_pair(8,1)]="**";
    m[make_pair(8,2)]="..";
    m[make_pair(9,0)]=".*";
    m[make_pair(9,1)]="*.";
    m[make_pair(9,2)]="..";
    m[make_pair(0,0)]=".*";
    m[make_pair(0,1)]="**";
    m[make_pair(0,2)]="..";
    c={"*.","..",".."};
    n[c]=1;
    c.clear();
    c={"*.","*.",".."};
    n[c]=2;
    c.clear();
    c={"**","..",".."};
    n[c]=3;
    c.clear();
    c={"**",".*",".."};
    n[c]=4;
    c.clear();
    c={"*.",".*",".."};
    n[c]=5;
    c.clear();
    c={"**","*.",".."};
    n[c]=6;
    c.clear();
    c={"**","**",".."};
    n[c]=7;
    c.clear();
    c={"*.","**",".."};
    n[c]=8;
    c.clear();
    c={".*","*.",".."};
    n[c]=9;
    c.clear();
    c={".*","**",".."};
    n[c]=0;
    c.clear();
    int D;
    while(cin>>D)
    {
        if(D==0)break;
        char s;
        cin>>s;
        if(s=='S')
        {
            string a;
            cin>>a;
            for(int j=0;j<3;j++)
            for(int i=0;i<D;i++)
            {
                if(i<D-1)cout<<m[make_pair(a[i]-'0',j)]<<" ";
                else cout<<m[make_pair(a[i]-'0',j)]<<"\n";
            }
        }
        else
        {
            vector<vector<string> >g(D,vector<string>(0));
            string a;
            for(int j=0;j<3;j++)
            {
                for(int i=0;i<D;i++)
                {
                    cin>>a;
                    g[i].push_back(a);
                }
            }
            for(int i=0;i<D;i++)
            {
                if(i<D-1)cout<<n[g[i]];
                else cout<<n[g[i]]<<"\n";
            }
        }

    }
}
