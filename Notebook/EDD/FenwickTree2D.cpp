#include "../Header.cpp"

struct BIT2D { // BIT = binary indexed tree (a.k.a. Fenwick Tree)
    /*

       ********All Index starts at 1**********

    */
    vector<vector<int> > bit;
    BIT2D(int n,int m) { bit.assign(n+1, vector<int>(m+1,0)); }
    // prefix sum query (sum in range 1 .. k)
    int psq(int k, int y) {
        int sum = 0;
        for (; k; k -= (k & -k))for (int ty=y; ty; ty -= (ty & -ty)) sum += bit[k][ty];
        return sum;
    }
    // range sum query (sum in range a .. b)
    int rsq(int x1, int y1, int x2, int y2) {
        return psq(x2,y2) - psq(x1-1,y2)- psq(x2,y1-1) + psq(x1-1,y1-1);
    }
    // increment k'th value by v (and propagate)
    void add(int k, int y, int v) {
        for (; k < bit.size(); k += (k & -k)) for (int ty=y; ty < bit[k].size(); ty += (ty & -ty)) bit[k][ty]+=v;
    }
    void set(int k, int y, int v)
    {
        int aux=rsq(k,y,k,y);
        for (; k < bit.size(); k += (k & -k)) for (int ty=y; ty < bit[k].size(); ty += (ty & -ty)) bit[k][ty]+=v-aux;
    }
};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        BIT2D ft2d(n+1,n+1);

        string s;
        while(cin>>s)
        {
            int x,y,v,x2,y2;
            if(s=="END")break;
            if(s=="SET")
            {
                cin>>x>>y>>v;
                ft2d.set(x+1,y+1,v);
            }
            else
            {
                cin>>x>>y>>x2>>y2;
                cout<<ft2d.rsq(x+1,y+1,x2+1,y2+1)<<"\n";
            }
        }
    }
}
