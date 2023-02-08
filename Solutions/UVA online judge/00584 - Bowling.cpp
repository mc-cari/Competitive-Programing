#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e14
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=525
int main()
{
    string s;
    while(getline(cin,s))
    {
        if(s=="Game Over")break;
        int sum=0;
        vl pend(30,0);
        int pos=0,aux=0,auxsum=0,roll=0;
        for(int i=0;i<s.length();i+=2)
        {
            if(pos>=9)
            {
                if(isdigit(s[i]))
                {
                    if(aux==0&&pos!=11)
                    {

                        auxsum+=s[i]-'0';
                        sum+=pend[roll]*auxsum;
                        aux++;
                    }
                    else
                    {
                        auxsum+=s[i]-'0';
                        sum+=auxsum+(s[i]-'0')*pend[roll];
                        aux=0;
                    }
                }
                else if(s[i]=='X')
                {
                    sum+=10+10*pend[roll];
                }
                else
                {
                    sum+=10+(10-auxsum)*pend[roll];
                    auxsum=0;
                    aux=1;
                }


                pos++;
            }
            else{
                if(aux==1)
                {
                   if(isdigit(s[i]))
                    {
                        auxsum+=s[i]-'0';
                        sum+=(s[i]-'0')*pend[roll];
                        sum+=auxsum;
                        pos++;
                    }
                    else
                    {
                        sum+=10+(10-auxsum)*pend[roll];
                        pend[roll+1]++;
                        pos++;
                    }
                    aux=0;
                    auxsum=0;
                }
                else{
                    if(isdigit(s[i]))
                    {
                        auxsum+=s[i]-'0';
                        sum+=auxsum*pend[roll];
                        aux=1;
                    }
                    else
                    {
                        sum+=10+10*pend[roll];
                        pend[roll+1]++;
                        pend[roll+2]++;
                        pos++;
                    }
                }
            }
            roll++;
        }
        cout<<sum<<"\n";


    }

}
