#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
#define INF 1e12
double pi = 2 * acos(0.0);
#define ALL(x) x.begin() , x.end()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
vector<int>solution;
vector<vector<int> >all_solutions;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2026
bool is_safe(int pos, int value)
{
    for(int i=0;i<solution.size();i++)
    {
        if(solution[i]==-1)continue;
        if(solution[i]==value)
        {
            return false;
        }
        if(abs(value-solution[i])==abs(pos-i))
        {
            return false;
        }
    }
    return true;
}

void solver(int pos)
{

    if(pos==8)
    {
        all_solutions.push_back(solution);
        return;
    }

    for(int value=0;value<8;value++)
    {
        if(is_safe(pos,value))
        {
            solution[pos]=value;

            solver(pos+1);

            solution[pos]=-1;
        }
    }
    return;
}




int main()
{
    solution.assign(8,-1);
    solver(0);
    int x;
    int t=1;
    while(cin>>x)
    {
        vl c;
        c.push_back(x);
        for(int i=0;i<7;i++)
        {
            cin>>x;
            c.push_back(x);
        }
        int mini=INF;
        for(int i=0;i<all_solutions.size();i++)
        {
            int sum=0;
            for(int j=0;j<8;j++)
            {
                if(c[j]!=all_solutions[i][j]+1)sum++;
            }
            mini=min(mini,sum);
        }
        cout<<"Case "<<t<<": "<<mini<<"\n";
        t++;
    }
    return 0;
}
