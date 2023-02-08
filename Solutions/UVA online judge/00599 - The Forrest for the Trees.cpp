#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=540

int main() {
    int t;cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        vector<vl>grafo(28,vl(0));
        while(s[0]!='*')
        {
            grafo[s[1]-'A'].push_back(s[3]-'A');
            grafo[s[3]-'A'].push_back(s[1]-'A');
            cin>>s;
        }
        cin>>s;
        vector<int>c;
        for(int i=0;i<s.length();i+=2)
        {
            c.push_back(s[i]-'A');
        }
        vector<bool> visitado(28,false);
        int tree=0,cnt=0;
        for(int i=0;i<c.size();i++)
        {
            stack<ll> q;
            if(grafo[c[i]].size()==0)
            {
                cnt++;
                continue;
            }
            if(visitado[c[i]])continue;
            tree++;
            q.push(c[i]);
            while(!q.empty()){

                ll t=q.top();
                q.pop();
                if(!visitado[t]){

                    visitado[t]=true;
                    for(ll i=0;i<grafo[t].size();i++){

                        if(!visitado[grafo[t][i]])
                        {

                                     q.push(grafo[t][i]);
                        }       }
                }
            }
        }
        cout<<"There are "<<tree<<" tree(s) and "<<cnt<<" acorn(s).\n";
    }


}
