#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
string s,r;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=673&mosmsg=Submission+received+with+ID+24591560
void back_track(int in,stack<char>& c, string& sol, vector<char>& track)
{
    if(sol!=r.substr(0,sol.size()))return;
    if(in==s.length()&&c.empty())
    {
        if(sol==r)
        {
            //cout<<sol<<endl;
            for(int i=0;i<track.size();i++)
            {
                cout<<track[i];
                i<track.size()-1 ? cout<<" " : cout<<"\n";
            }
        }
        return;
    }
    if(in<s.length())
    {
        c.push(s[in]);
        track.push_back('i');
        back_track(in+1,c,sol,track);
        track.pop_back();
        c.pop();
    }
    if(!c.empty())
    {
        string aux2=sol;
        sol=sol+c.top();

        char aux=c.top();
        c.pop();
        track.push_back('o');
        back_track(in,c,sol,track);
        c.push(aux);
        track.pop_back();
        sol=aux2;
    }



}


int main()
{

    while(cin>>s)
    {
        cin>>r;
        stack<char>c;
        string sol="";
        vector<char> track;
        cout<<"[\n";
        back_track(0,c,sol,track);
        cout<<"]\n";

    }

}
