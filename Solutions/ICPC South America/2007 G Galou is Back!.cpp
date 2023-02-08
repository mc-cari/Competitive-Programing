#include<bits/stdc++.h>
//https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1934
using namespace std;
typedef long long  ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12


int main()
{
    ll R,C;
    while(cin>>R>>C){
        if(R+C==0)
            break;
        cout<<"\n";
        ll v,x,y,e,in=-1;
        vl co(C*R,0);
        vector<vl > grafo(R*C,vl(0));
        vector<string>s;
        for(ll i=0;i<R;i++)
        {
            string S;
            cin>>S;
            for(ll j=0;j<S.length();j++)
            {
                if(S[j]=='I')
                {
                    co[i*C+j]=1;
                }

            }
            s.push_back(S);
        }
        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                string S=s[i];
                if(S[j]=='I'||S[j]=='*')
                    {
                        if(j<S.length()-1)
                        {
                            if(S[j+1]=='I'||S[j+1]=='*')
                            {
                                grafo[C*i+j].push_back(C*i+j+1);
                            }
                        }
                        if(i>0)
                        {
                            if(s[i-1][j]=='I'||s[i-1][j]=='*')
                            {
                                grafo[C*i+j].push_back(C*(i-1)+j);
                            }
                            if(j<C+1&&(s[i-1][j+1]=='I'||s[i-1][j+1]=='*'))
                            {
                                grafo[C*i+j].push_back(C*(i-1)+j+1);
                            }
                        }
                        if(j>0)
                        {
                            if(S[j-1]=='I'||S[j-1]=='*')
                            {
                                grafo[C*i+j].push_back(C*i+j-1);
                            }
                        }
                        if(i<R-1)
                        {
                            if(s[i+1][j]=='I'||s[i+1][j]=='*')
                            {
                                grafo[C*i+j].push_back(C*(i+1)+j);
                            }
                            if(j>0&&(s[i+1][j-1]=='I'||s[i+1][j-1]=='*'))
                            {
                                grafo[C*i+j].push_back(C*(i+1)+j-1);
                            }
                        }
                    }
            }
        }
        vector<bool> prev(R*C,false);
        for(int k=0;k<R*C;k++)
        {

            if(!prev[k]&&s[k/C][k%C]=='I'){
                vector<bool>visitado(prev);
                bool o=0;
                queue<ll> q;
                q.push(k);
                while(!q.empty()){

                    ll t=q.front();
                    q.pop();
                    if(!visitado[t]){

                        visitado[t]=true;
                        for(ll i=0;i<grafo[t].size();i++){
                            if(co[t]==co[grafo[t][i]])
                            {
                                o=1;
                            }
                            if(!visitado[grafo[t][i]])
                            {
                                co[grafo[t][i]]=3-co[t];
                                q.push(grafo[t][i]);
                            }
                        }
                    }
                    if (o) break;
                }
                if(o)
                {
                    vector<bool>visitado(prev);
                    queue<ll> q;
                    q.push(k);
                    while(!q.empty()){

                        ll t=q.front();
                        q.pop();
                        if(!visitado[t]){
                            co[t]=-1;
                            visitado[t]=true;
                            for(ll i=0;i<grafo[t].size();i++){

                                if(!visitado[grafo[t][i]])
                                {

                                    q.push(grafo[t][i]);
                                }
                            }
                        }
                    }
                }
                prev=visitado;
            }
        }
        for(int i=0;i<R;i++)
        {
            for(int j=0;j<C;j++)
            {
                if(s[i][j]=='.')
                {
                    cout<<s[i][j];
                }
                else if(co[i*C+j]==1)
                {
                    cout<<'(';
                }
                else if(co[i*C+j]==2)
                    cout<<')';
                else if(co[i*C+j]==0)
                    cout<<'F';
                else if(co[i*C+j]==-1)
                    cout<<'B';
            }cout<<endl;
        }
    }

	return 0;
}
