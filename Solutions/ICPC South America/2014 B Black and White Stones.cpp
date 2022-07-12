#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1744
int main()
{
    int A,B,C;
    while(cin>>A>>B)
    {
        C=A/(A-B);
        int W=0;
        string s;
        cin>>s;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='B')W++;
        }
        int prev=-1;
        for(int i=W-1;i>=0;i--)
        {
            if(s[i]=='W')
            {
                prev=i;
                break;
            }
        }
        if(prev==-1)
        {
            cout<<"0\n";
            continue;
        }
        ll sum=0;
        for(int i=W;i<s.length();i++)
        {
            if(s[i]=='B')
            {
                //cout<<i<<" "<<prev<<" "<<C<<endl;
                if(i-prev<=C)
                {

                    sum+=(i-prev)*(A-B);
                    s[i]=='W';
                    s[prev]='B';
                    for(int j=prev-1;j>=0;j--)
                    {
                        if(s[j]=='W')
                        {
                            prev=j;
                            break;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }
        for(int i=0;i<W;i++)
        {
            if(s[i]=='W')sum+=A;
        }
        cout<<sum<<"\n";
    }
}
