#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3703
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {

        int k;
        cin>>k;
        string s;
        vector<string>d;
        map<string,bool>m,vis;
        vector<vector<char> >c(5,vector<char>(0));
        for(int i=0;i<6;i++)
        {
            for(int j=0;j<5;j++)
            {
                char x;
                cin>>x;
                c[j].push_back(x);
            }
        }
        for(int i=0;i<5;i++)
        {
            sort(ALL(c[i]));
        }

        for(int i=0;i<6;i++)
        {
            cin>>s;
            d.push_back(s);
        }
        for(int a1=0;a1<6;a1++)
        {
            for(int a2=0;a2<6;a2++)
                for(int a3=0;a3<6;a3++)
                    for(int a4=0;a4<6;a4++)
                        for(int a5=0;a5<6;a5++)
                        {
                            string z="     ";
                            z[0]=d[a1][0];
                            z[1]=d[a2][1];
                            z[2]=d[a3][2];
                            z[3]=d[a4][3];
                            z[4]=d[a5][4];
                            m[z]=1;
                        }
        }

        string prev=" ";
        int in=0;
        bool o=1;
        for(int a1=0;a1<6&&o;a1++)
        {
            for(int a2=0;a2<6&&o;a2++)
                for(int a3=0;a3<6&&o;a3++)
                    for(int a4=0;a4<6&&o;a4++)
                        for(int a5=0;a5<6&&o;a5++)
                        {
                            string z="     ";
                            z[0]=c[0][a1];
                            z[1]=c[1][a2];
                            z[2]=c[2][a3];
                            z[3]=c[3][a4];
                            z[4]=c[4][a5];
                            if(!vis[z]&&m[z])
                            {

                                in++;
                                prev=z;
                                vis[z]=1;
                                if(in==k){o=0;break;}
                            }
                        }
        }
        if(o)cout<<"NO\n";
        else cout<<prev<<"\n";
    }
}
