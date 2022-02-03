#include <bits/stdc++.h>
using namespace std;

vector<int>solution;
vector<vector<int> >all_solutions;

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

void solver(int row,int col, int pos)
{
    if(pos==col)
    {
        pos=pos+1;
    }
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

            solver(row,col,pos+1);

            solution[pos]=-1;
        }
    }
    return;
}




int main()
{
    int t;
    cin>>t;
    for(int k=0;k<t;k++)
    {
        int row,col;
        cin>>row>>col;
        row--;col--;

        solution.assign(8,-1);
        solution[col]=row;
        solver(row,col,0);

        if(k>0)
        {
            cout<<"\n";
        }
        cout<<"SOLN       COLUMN\n";
        cout<<" #      1 2 3 4 5 6 7 8\n\n";
        for(int n=0;n<all_solutions.size();n++)
        {
            if (n<9)
            {
                cout <<" "<<n+1<<"      ";
            }
            else
            {
                cout<<n+1<< "      ";
            }
            for(int i=0;i<8;i++)
            {
                cout<<all_solutions[n][i]+1;
                if (i<7)
                {
                    cout<<" ";
                }
            }
            cout<<"\n";
        }
        all_solutions.clear();
    }
    return 0;
}
