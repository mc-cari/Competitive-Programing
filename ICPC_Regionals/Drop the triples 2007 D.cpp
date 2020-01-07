#include<bits/stdc++.h>
using namespace std;
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1931
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
bool check(int a,int b,int c)
{
    return (a+b>c&&a+c>b&&c+b>a);
}
vl A,B;
ll acuma,acumb;
vector<unordered_map<bitset<27>,int> >memo1,memo2;
int DP1(int trio, bitset<27>&b)
{
    if(trio*3>=A.size())
    {
        return 0;
    }
    if(memo1[trio].count(b))return memo1[trio][b];
    int sum=0;
    for(int i=0;i<A.size();i++)
    {
        if(!b[i])
        {
            for(int j=i+1;j<A.size();j++)
            {
                if(!b[j])
                {
                    bool o=0;
                    for(int z=j+1;z<A.size();z++)
                    {
                        if(!b[z]&&check(A[i],A[j],A[z]))
                        {
                            b[i]=1;
                            b[j]=1;
                            b[z]=1;
                            sum=max(sum,1+DP1(trio+1,b));
                            b[i]=0;
                            b[j]=0;
                            b[z]=0;
                            o=1;
                            break;
                        }
                    }
                    if(o)break;
                }

            }
        }
    }
    return memo1[trio][b]=sum;
}

int DP2(int trio, bitset<27>&b)
{
    if(trio*3>=B.size())
    {
        return 0;
    }
    if(memo2[trio].count(b))return memo2[trio][b];
    int sum=0;
    for(int i=0;i<B.size();i++)
    {
        if(!b[i])
        {
            for(int j=i+1;j<B.size();j++)
            {
                if(!b[j])
                {
                    bool o=0;
                    for(int z=j+1;z<B.size();z++)
                    {
                        if(!b[z]&&check(B[i],B[j],B[z]))
                        {
                            b[i]=1;
                            b[j]=1;
                            b[z]=1;
                            sum=max(sum,1+DP2(trio+1,b));
                            b[i]=0;
                            b[j]=0;
                            b[z]=0;
                            o=1;
                            break;
                        }
                    }
                    if(o)break;
                }

            }
        }
    }
    return memo2[trio][b]=sum;
}
int main()
{
    int n,x;
    while(cin>>n)
    {
        if(n==0)
        {
            break;
        }
        vl a(15,0),b(15,0);
        A.clear();
        B.clear();
        for(int i=0;i<n;i++)
        {
            cin>>x;
            if(i%2==0)
            {
                a[x]++;
            }
            else
            {
                b[x]++;
            }
        }
        int suma=0,sumb=0;acuma=0;acumb=0;
        for(int i=1;i<=13;i++)
        {
            suma+=a[i]/3;
            if(a[i]%3>0)
            {
                A.push_back(i);
            }
            if(a[i]%3==2)
                A.push_back(i);
        }
        for(int i=1;i<=13;i++)
        {
            sumb+=b[i]/3;
            if(b[i]%3>0)
            {
                B.push_back(i);
            }
            if(b[i]%3==2)
                B.push_back(i);
        }

        memo1.clear();
        unordered_map<bitset<27>, int> ax;
        bitset<27> z;
        memo1.assign(9, ax);
        memo2.clear();
        memo2.assign(9, ax);

        acuma=DP1(0,z);
        acumb=DP2(0,z);
        //cout<<suma<<" "<<sumb<<" "<<acuma<<" "<<acumb<<endl;
        if(suma>sumb)
        {
            cout<<"1\n";
        }
        else if(suma<sumb){
            cout<<"2\n";
        }
        else{
            if(acuma>acumb)
            {
                cout<<"1\n";
            }
            else if(acuma<acumb)
            {
                cout<<"2\n";
            }
            else cout<<"0\n";
        }
    }
    return 0;
}
