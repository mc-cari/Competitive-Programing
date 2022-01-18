#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
int n;
bool o;
vector<string>ver;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=357
void back_track(int in, int prev,vector<string>& s,vl nul)
{
    if(o)return;
    if(in==n)
    {
        o=1;
        return;
    }
    if(prev<0)return;
    bool o2=1;
    vl aux;
    for(int i=0;i<7;i++)
    {
        if(s[in][i]=='Y'&&ver[prev][i]!='Y')
        {
            o2=0;
        }
        if(s[in][i]=='Y'&&nul[i])o2=0;
        if(s[in][i]=='N'&&ver[prev][i]=='Y')aux.push_back(i);
    }
    if(o2)
    {
        vl aux2=nul;
        for(int i=0;i<aux.size();i++)
        {
            nul[aux[i]]=1;
        }
        back_track(in+1,prev-1,s,nul);
        nul.clear();
        nul.assign(ALL(aux2));
    }
}

int main ()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    ver.push_back("YYYYYYN");
    ver.push_back("NYYNNNN");
    ver.push_back("YYNYYNY");
    ver.push_back("YYYYNNY");
    ver.push_back("NYYNNYY");
    ver.push_back("YNYYNYY");
    ver.push_back("YNYYYYY");
    ver.push_back("YYYNNNN");
    ver.push_back("YYYYYYY");
    ver.push_back("YYYYNYY");
    while(cin>>n)
    {
        if(n==0)break;
        vector<string>s;
        string x;
        o=0;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            s.push_back(x);
        }
        for(int i=0;i<=9;i++){
            vl nul(7,0);
            back_track(0,i,s,nul);
        }
        if(o)cout<<"MATCH\n";
        else cout<<"MISMATCH\n";
    }

}
