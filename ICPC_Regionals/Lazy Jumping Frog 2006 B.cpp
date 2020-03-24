#include <bits/stdc++.h>
using namespace std;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/1384

int main()
{
    vector<vector<int> >v(1000,vector<int>(1000,0));
    vector<vector<int> >p(1000,vector<int>(1000,INF));
    int mov[5][5];
    mov[0][0]=7;
    mov[0][1]=6;
    mov[0][2]=5;
    mov[0][3]=6;
    mov[0][4]=7;
    mov[1][0]=6;
    mov[1][1]=3;
    mov[1][2]=2;
    mov[1][3]=3;
    mov[1][4]=6;
    mov[2][0]=5;
    mov[2][1]=2;
    mov[2][2]=-1;
    mov[2][3]=2;
    mov[2][4]=5;
    mov[3][0]=6;
    mov[3][1]=3;
    mov[3][2]=2;
    mov[3][3]=3;
    mov[3][4]=6;
    mov[4][0]=7;
    mov[4][1]=6;
    mov[4][2]=5;
    mov[4][3]=6;
    mov[4][4]=7;
    int c,r,cf,rf,ct,rt,w,c1,r1,c2,r2,x,y;
    while(cin>>c>>r&&c+r!=0)
    {
        for(int i=0;i<c;i++)
        {
            for(int j=0;j<r;j++)
            {
                v[i][j]=0;
                p[i][j]=INF;
            }
        }
        cin>>cf>>rf>>ct>>rt;
        cf--;
        rf--;
        ct--;
        rt--;
        cin>>w;
        for(int k=0;k<w;k++)
        {
            cin>>c1>>r1>>c2>>r2;
            if(cf==ct&&rf==rt)continue;
            c1--;r1--;c2--;r2--;
            for(int i=c1;i<=c2&&i-c1<2;i++)
            {
                for(int j=r1;j<=r2;j++)
                {
                    v[i][j]=1;
                }
            }
            if(c2-c1>1){
            for(int i=c2-1;i<=c2;i++)
            {
                if(i<c1)continue;
                for(int j=r1;j<=r2;j++)
                {
                    v[i][j]=1;
                }
            }
            }
            for(int j=r1;j<=r2&&j-r1<2;j++)
            {
                for(int i=c1;i<=c2;i++)
                {
                    v[i][j]=1;
                }
            }
            if(r2-r1>1){
            for(int j=r2-1;j<=r2;j++)
            {
                if(j<r1)continue;
                for(int i=c1;i<=c2;i++)
                {
                    v[i][j]=1;
                }
            }
            }
        }
        if(cf==ct&&rf==rt)
        {
            cout<<0<<endl;
            continue;
        }
        pair<int,pair<int,int> >h;
        priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > >q;
        q.push(make_pair(0,make_pair(cf,rf)));
        while(!q.empty())
        {
            x=q.top().second.first;
            y=q.top().second.second;
            int pe=q.top().first;
            q.pop();
            if(!v[x][y])
            {
            v[x][y]=1;
            for(int i=x-2;i<=x+2;i++)
            {
                for(int j=y-2;j<=y+2;j++)
                {
                    if(i==x&&j==y)continue;
                    if(i>=0&&i<c&&j>=0&&j<r&&!v[i][j]&&mov[i+2-x][j+2-y]+pe<p[i][j])
                    {
                        p[i][j]=mov[i+2-x][j+2-y]+pe;
                        q.push(make_pair(p[i][j],make_pair(i,j)));
                    }
                }
            }
            }
        }
        if(p[ct][rt]==INF)cout<<"impossible\n";
        else cout<<p[ct][rt]<<"\n";
    }

    return 0;
}
