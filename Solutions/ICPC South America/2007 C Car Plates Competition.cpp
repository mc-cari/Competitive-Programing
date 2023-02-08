#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e8
//https://www.urionlinejudge.com.br/judge/es/problems/view/1363
bool old(string x)
{
    if(!isdigit(x[0])&&!isdigit(x[1])&&!isdigit(x[2])&&!isdigit(x[3])&&!isdigit(x[4]))
    {
        return false;
    }return true;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string a,b;
    ll c;
    while(cin>>a>>b>>c)
    {
        bool oa=old(a),ob=old(b);
        if(a=="*")
            break;
        bool o=0;
        if(!ob)
        {
            for(ll i=0;i<5;i++)
            {
                if(b[i]=='A'||b[i]=='C'||b[i]=='I'||b[i]=='P'||b[i]=='M')
                {
                    o=1;
                }
            }
            if(o)
            {
                cout<<"N\n";
                continue;
            }
        }
        if((ob&&!oa)||a==b||(isdigit(b[3])&&!isdigit(b[4]))||(isdigit(b[4])&&!isdigit(b[3])))
        {
            cout<<"N\n";
            continue;
        }
        if(ob==oa)
        {
            if(a>=b)
            {
                cout<<"N\n";
                continue;
            }
        }
        string x=a,y=b;
        ll sum=0;
        if(!old(y)&&y!=a)
        {
            if(old(x))x="BBBBB00";
            if(x[6]!=y[6])
            {
                if(x[6]<y[6])
                {
                    sum+=y[6]-x[6];
                }
                else
                {
                    sum+=10-(x[6]-y[6]);
                    ll in=5;
                    while(y[in]=='0'||y[in]=='B')
                    {
                        if(y[in]=='0')
                            y[in]='9';
                        else
                            y[in]='Z';
                        in--;
                    }
                    y[in]=char(y[in]-1);
                    if((y[in]=='A'||y[in]=='C'||y[in]=='I'||y[in]=='P'||y[in]=='M'))
                    {
                        y[in]=char(y[in]-1);
                    }
                }
                y[6]=x[6];
            }
            if(y[5]!=x[5])
            {
                if(x[5]<y[5])
                {
                    sum+=(y[5]-x[5])*10;
                }
                else
                {
                    sum+=10*(10-(x[5]-y[5]));
                    ll in=4;
                    while(y[in]=='0'||y[in]=='B')
                    {
                        if(y[in]=='0')
                            y[in]='9';
                        else
                            y[in]='Z';
                        in--;
                    }
                    y[in]=char(y[in]-1);
                    if((y[in]=='A'||y[in]=='C'||y[in]=='I'||y[in]=='P'||y[in]=='M'))
                    {
                        y[in]=char(y[in]-1);
                    }
                }
                y[5]=x[5];
            }
            vl p={19448100,926100,44100,2100,100};
            for(ll j=4;j>=0;j--)
            {
                if(x[j]!=y[j])
                {
                    bool op=0;
                    ll cont=0;
                    for(ll i=0;i<27&&x[j]!=y[j];i++)
                    {
                        if(y[j]=='B')
                        {
                            y[j]='Z';
                            op=1;
                        }
                        else
                            y[j]=char(y[j]-1);
                        if(y[j]=='C'||y[j]=='I'||y[j]=='P'||y[j]=='M')
                        {
                            y[j]=char(y[j]-1);
                        }
                        cont++;
                    }
                    sum+=(cont)*p[j];
                    if (op&&j!=0)
                    {
                        ll in=j-1;
                        while(y[in]=='0'||y[in]=='B')
                        {
                            if(y[in]=='0')
                                y[in]='9';
                            else
                                y[in]='Z';
                            in--;
                        }
                        y[in]=char(y[in]-1);
                        if((y[in]=='A'||y[in]=='C'||y[in]=='I'||y[in]=='P'||y[in]=='M'))
                        {
                            y[in]=char(y[in]-1);
                        }
                    }
                    y[j]=x[j];
                }
            }
        }
        if(y!=a)
        {
            if(y=="BBBBB00")
            {
                y="ZZZ9999";
                sum++;
            }
            if(y!=a)
            {
                if(a[6]!=y[6])
                {
                    if(a[6]<y[6])
                    {
                        sum+=y[6]-a[6];
                    }
                    else
                    {
                        sum+=10-(a[6]-y[6]);
                        ll in=5;
                        while(y[in]=='0'||y[in]=='A')
                        {
                            if(y[in]=='0')
                                y[in]='9';
                            else
                                y[in]='Z';
                            in--;
                        }
                        y[in]=char(y[in]-1);
                    }
                    y[6]=a[6];
                }
                if(a[5]!=y[5])
                {
                    if(a[5]<y[5])
                        sum+=(y[5]-a[5])*10;
                    else
                    {
                        sum+=(10-(a[5]-y[5]))*10;
                        ll in=4;
                        while(y[in]=='0'||y[in]=='A')
                        {
                            if(y[in]=='0')
                                y[in]='9';
                            else
                                y[in]='Z';
                            in--;
                        }
                        y[in]=char(y[in]-1);
                    }
                    y[5]=x[5];
                }
                if(a[4]!=y[4])
                {
                    if(a[4]<y[4])
                        sum+=(y[4]-a[4])*100;
                    else
                    {
                        sum+=(10-(a[4]-y[4]))*100;
                        ll in=3;
                        while(y[in]=='0'||y[in]=='A')
                        {
                            if(y[in]=='0')
                                y[in]='9';
                            else
                                y[in]='Z';
                            in--;
                        }
                        y[in]=char(y[in]-1);
                    }
                    y[4]=x[4];
                }
                if(a[3]!=y[3])
                {
                    if(a[3]<y[3])
                        sum+=(y[3]-a[3])*1000;
                    else
                    {
                        sum+=(10-(a[3]-y[3]))*1000;
                        ll in=2;
                        while(y[in]=='0'||y[in]=='A')
                        {
                            if(y[in]=='0')
                                y[in]='9';
                            else
                                y[in]='Z';
                            in--;
                        }
                        y[in]=char(y[in]-1);
                    }
                    y[3]=x[3];
                }
                vl p={6760000,260000,10000};
                for(ll j=2;j>=0;j--)
                {
                    if(a[j]!=y[j])
                    {
                        bool op=0;
                        ll cont=0;
                        for(ll i=0;i<27&&a[j]!=y[j];i++)
                        {
                            if(y[j]=='A')
                            {
                                y[j]='Z';
                                op=1;
                            }
                            else
                                y[j]=char(y[j]-1);
                            cont++;
                        }
                        sum+=(cont)*p[j];
                        if (op&&j!=0)
                        {
                            ll in=j-1;
                            while(y[in]=='0'||y[in]=='A')
                            {
                                if(y[in]=='0')
                                    y[in]='9';
                                else
                                    y[in]='Z';
                                in--;
                            }
                            y[in]=char(y[in]-1);
                        }
                        y[j]=a[j];
                    }
                }
            }


        }
        if(sum<=c)
        {
            cout<<"Y\n";
        }
        else cout<<"N\n";
    }

}
