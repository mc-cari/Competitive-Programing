#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
//https://www.spoj.com/problems/HISTOGRA/
int main()
{
    int n;
    while(cin>>n)
    {
        if(n==0)break;
        vl c;
        ll x;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        vl left(n,0),right(n,0);
        stack<ll> d;
        for(int i=n-1;i>=0;i--)
        {
            if(d.empty())
            {
                d.push(i);
                right[i]=i;
            }
            else
            {
                while(!d.empty()&&c[d.top()]>=c[i])
                {
                    d.pop();
                }
                if(d.empty())
                {
                    d.push(i);
                    right[i]=n-1;
                }
                else
                {
                    right[i]=d.top()-1;
                    d.push(i);
                }
            }
        }
        while(!d.empty())d.pop();
        for(int i=0;i<n;i++)
        {
            if(d.empty())
            {
                d.push(i);
                left[i]=i;
            }
            else
            {
                while(!d.empty()&&c[d.top()]>=c[i])
                {
                    d.pop();
                }
                if(d.empty())
                {
                    d.push(i);
                    left[i]=0;
                }
                else
                {
                    left[i]=d.top()+1;
                    d.push(i);
                }
            }
        }
        ll maxi=-1;
        for(int i=0;i<n;i++)
        {
            maxi=max(maxi,c[i]*(right[i]-left[i]+1));
        }
        cout<<maxi<<"\n";

    }
}
