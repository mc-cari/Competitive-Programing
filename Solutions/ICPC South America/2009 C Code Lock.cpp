#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
string s;
int a[1001];
vector<vl> memo;
//https://www.urionlinejudge.com.br/judge/es/problems/view/1412
ll DP(int i,int prev,int level)
{
    if(i<0)return 0;
    if(level==s.length()||level==-s.length())return INF;
    if(memo[i][level+s.length()+1]!=-1)return memo[i][level+s.length()+1];
    ll mini=INF;
    if(level>=0){
        if(prev <= a[i])
            mini = min(mini,DP(i-1,a[i],level)+a[i]-prev);
        else{
            int aux = 26-(prev-a[i]);
            mini = min(mini,DP(i-1,a[i],level+1)+aux);
        }

        if(level>0 || a[i] < prev)
        {
            if(a[i] <= prev)
                mini = min(mini,DP(i-1,a[i],level));
            else
                mini = min(mini,DP(i-1,a[i],level-1));
        }
        int aux1=26-a[i];
        if(aux1==26)aux1=0;
        if(a[i]==0)
            mini=min(mini,DP(i-1,a[i],0)+aux1);
        else mini=min(mini,DP(i-1,a[i],-1)+aux1);
    }
    else{
        int aux1=(26-prev),aux2=(26-a[i]);
        if(prev==0)aux1=0;
        if(a[i]==0)aux2=0;
        if(aux1 <= aux2)
            mini=min(mini,DP(i-1,a[i],level)+aux2-aux1);
        else{
            int aux = 26-(aux1-aux2);
            mini=min(mini,DP(i-1,a[i],level-1)+aux);
        }

        if(level < -1 || aux1 > aux2)
        {
            if(aux1 >= aux2) mini=min(mini,DP(i-1,a[i],level));
            else mini=min(mini,DP(i-1,a[i],level+1));
        }
        mini=min(mini,DP(i-1,a[i],0)+a[i]);
    }
    return memo[i][level+s.length()+1]=mini;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while(cin>>s)
    {
        if(s=="*")break;
        memo.clear();
        memo.assign(s.length()+1,vl(2*s.length()+1,-1));
        for(int i=0;i<s.size();i++)
            a[i]=s[i]-'a';
        cout<<DP(s.length()-1,0,0)<<endl;
    }
}
