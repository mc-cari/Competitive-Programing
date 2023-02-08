#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=9
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int marked[5][5],num[5][5];

        memset(marked,0,sizeof(marked));
        marked[2][2]=1;
        num[2][2]=-1;
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(i==2&&j==2)continue;
                cin>>num[i][j];
            }
        }
        vl c;
        for(int i=0;i<75;i++)
        {
            int x;
            cin>>x;
            c.push_back(x);
        }
        int ans;
        for(int k=0;k<75;k++)
        {
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<5;j++)
                {
                    if(c[k]==num[i][j])
                    {
                        marked[i][j]=1;
                        break;
                    }
                }
            }
            int sum=0;
            bool o=0;
            for(int i=0;i<5;i++)
            {
                sum=0;
                for(int j=0;j<5;j++)
                {
                    if(marked[i][j])sum++;
                }
                if(sum==5)o=1;
            }
            for(int j=0;j<5;j++)
            {
                sum=0;
                for(int i=0;i<5;i++)
                {
                    if(marked[i][j])sum++;
                }
                if(sum==5)o=1;
            }
            if(marked[0][0]&&marked[1][1]&&marked[2][2]&&marked[3][3]&&marked[4][4])o=1;
            if(marked[0][4]&&marked[1][3]&&marked[2][2]&&marked[3][1]&&marked[4][0])o=1;
            if(o)
            {
                ans=k+1;
                break;
            }
        }
        cout<<"BINGO after "<<ans<<" numbers announced\n";
    }

}
