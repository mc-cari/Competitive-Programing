#include<bits/stdc++.h>
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2477
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
int Wats(int p)
{
    int a=p;
    int w=0;
    if(a<200)
    {
        w+=a/2;
    }
    else{
        w+=100;
        a-=200;
        if(a<9900*3)
        {
            w+=a/3;
        }
        else
        {
            //cout<<a<<endl;
            w+=9900;
            a-=9900*3;
            if(a<(1000000-10000)*5)
            {
                w+=a/5;
            }
            else
            {
                w+=1000000-10000;
                a-=(1000000-10000)*5;
                if(a>0)
                {
                    w+=a/7;
                }
            }
        }
    }
    return w;
}
int Precio(int w)
{
    int p=0;
    if(w<100)
    {
        p+=w*2;
    }
    else
    {
        p+=200;
        w-=100;
        if(w<9900)
        {
            p+=w*3;
        }
        else
        {
            w-=9900;
            p+=9900*3;
            if(w<1000000-10000)
            {
                p+=w*5;
            }
            else
            {
                p+=(1000000-10000)*5;
                w-=1000000-10000;
                p+=w*7;
            }
        }
    }
    return p;
}

int main()
{
    int A,B,n,x;
    while(cin>>A>>B)
    {
        if(A+B==0)break;
        int w=Wats(A);
        int total=w;
        int l=0,r=w,p;
        while(l<=r)
        {
            p=(l+r)/2;
            int d=Precio(total-p)-Precio(p);
            if(d>B)l=p+1;
            else if(d==B)
            {
                break;
            }
            else r=p-1;
        }
        cout<<Precio(p)<<endl;
    }

}
