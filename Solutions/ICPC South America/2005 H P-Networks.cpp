#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e8
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 

//https://www.urionlinejudge.com.br/judge/es/problems/view/1274

int sim(deque<ll>& ans, vl& aux, ll in)
{
    for(int i = 0; i < aux.size(); i++)
    {
        if(aux[i] == in - 1)
        {
            in--;
        }
        else if(aux[i] == in)
        {
            in++;
        }
    }
    for(int i = 0; i < ans.size(); i++)
    {
        if(ans[i] == in - 1)
        {
            in--;
        }
        else if(ans[i] == in)
        {
            in++;
        }
    }
    return in;
}
bool check(deque<ll>& ans, vl& aux, vl order, ll in)
{
    for(int i = 0; i <= in; i++)
    {
        if(sim(ans, aux, i) != order[i])
        {
            return 0;
        }
    }
    return 1;
}


int main()
{
    int n, x;
    while(cin >> n && n){
        vl order;
        deque<ll>ans;
        for(int i = 0; i < n; i++)
        {
            cin >> x;
            order.push_back(x-1);
        }
        bool p = 1;
        for(int i = 0; i < n; i++)
        {
            vl aux;
            if(check(ans, aux, order, i))
            {
                continue;
            }
            bool o = 0;
            for(int j = i + 1; j < n; j++)
            {
                aux.push_back(j - 1);
                if(check(ans, aux, order, i))
                {
                    o = 1;
                    break;
                }

            }
            if (o)
            {
                while(!aux.empty())
                {
                    ans.push_front(aux.back());
                    aux.pop_back();
                }
                continue;
            }
            aux.clear();
            o = 0;
            for(int j = i - 1; j >= 0; j--)
            {
                aux.push_back(j);
                if(check(ans, aux, order, i))
                {
                    o = 1;
                    break;
                }

            }
            if (o)
            {
                while(!aux.empty())
                {
                    ans.push_front(aux.back());
                    aux.pop_back();
                }
                continue;
            }
            p = 0;
            break;
        }
        if(!p)
        {
            cout<<"No solution\n";
        }
        else
        {
            cout<<ans.size();
            for(auto it : ans)
            {
                cout<<" "<<it+1;
            }
            cout<<"\n";
        }
    }
  
  
}
