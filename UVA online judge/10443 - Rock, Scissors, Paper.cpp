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
    map<char,char>a;
    a['R']='S';
    a['S']='P';
    a['P']='R';
    while(t--)
    {
        int r,c,n;
        char x;
        cin>>r>>c>>n;
        vector<vector<char> >C(r,vector<char>(c,'a')),aux(r,vector<char>(c,'a'));
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                cin>>x;
                C[i][j]=x;
                aux[i][j]=x;
            }
        }
        for(int k=0;k<n;k++)
        {
            for(int i=0;i<r;i++)
            {
                for(int j=0;j<c;j++)
                {

                    if(i!=0&&a[C[i][j]]==C[i-1][j])
                    {
                        aux[i-1][j]=C[i][j];
                    }
                    if(j!=0&&a[C[i][j]]==C[i][j-1])
                    {
                        aux[i][j-1]=C[i][j];
                    }
                    if(i!=r-1&&a[C[i][j]]==C[i+1][j])
                    {
                        aux[i+1][j]=C[i][j];
                    }
                    if(j!=c-1&&a[C[i][j]]==C[i][j+1])
                    {
                        aux[i][j+1]=C[i][j];
                    }
                }
            }

            C=aux;
        }
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                cout<<C[i][j];
            }
            cout<<"\n";
        }
        if(t!=0)cout<<"\n";
    }
}
