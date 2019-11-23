#include <bits/stdc++.h>
using namespace std;
//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=41
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    map<int,int>c;
    map<int,int>::reverse_iterator it;
    vector<pair<int,int> >d;
    int l,r,h;
    while(cin>>l)
    {
        cin>>h>>r;
        d.push_back(make_pair(l,h));
        d.push_back(make_pair(r,-h));
    }
    sort(d.begin(),d.end());
    int maxi=-1,prev=d[0].first,o=1;
    for(int i=0;i<d.size();i++)
    {
        h=d[i].second;
        if(h>0)
        {
            c[h]++;
            if(maxi<h)
            {
                maxi=h;
                o=1;
            }
        }
        else
        {
            h=-h;
            c[h]--;
            if(c[maxi]==0)
            {

                maxi=0;
                for(it=c.rbegin();it!=c.rend();it++)
                {
                    if((*it).second!=0)
                    {
                        maxi=(*it).first;
                        break;
                    }
                }
                o=1;
            }
        }
        if(i==d.size()-1)
        {
            cout<<d[d.size()-1].first<<" "<<maxi<<"\n";
        }
        else if(d[i+1].first!=d[i].first&&o)
        {
            cout<<d[i].first<<" "<<maxi<<" ";
            o=0;
        }
    }

}
