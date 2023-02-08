#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1311
int main()
{
    int S,B;
    while(cin>>S>>B)
    {
        if(S+B==0)
        {
            break;
        }
        list<int>c;
        vector<list<int>::iterator >d;
        for(int i=1;i<=S;i++)
        {
            c.push_back(i);
        }
        list<int>::iterator it,L,R;
        for(it =c.begin();it!=c.end();it++)
        {
            d.push_back(it);
        }
        int l,r;
        for(int i=0;i<B;i++)
        {
            cin>>l>>r;
            L=d[l-1];
            R=d[r-1];
            R=next(R);
            if(L==c.begin())
            {
                cout<<"* ";
            }
            else cout<<*prev(L)<<" ";
            if(R==c.end())
                cout<<"*\n";
            else cout<<*R<<"\n";
            c.erase(L,R);
        }
        cout<<"-\n";
    }
}
