#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e12
#define EPS 1e-7
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://www.urionlinejudge.com.br/judge/es/problems/view/1499

ll N, Q, dQ = 0, dN = 0;

vl d_N, d_Q;

ll get_far(vector<vl> &g, ll n, ll inicio, bool op)
{
    vl v(n, 0);
    vl d(n, INF);

    ll obj = inicio, dis = 0;

    d[inicio] = 0;
    queue<ll> q;
    q.push(inicio);
    while(!q.empty()){

        ll t = q.front();
        q.pop();

        if(!v[t]){
            
            
            v[t] = 1;
            for(auto it : g[t]){

                if(!v[it])
                {
                    
                    d[it] = d[t]+1;
                    if(d[it] > dis)
                    {
                        dis = d[it];
                        obj = it;
                    }
                    q.push(it);
                }
            }
        }
    }

    if(op)
        dQ = dis;
    else
        dN = dis;

  

    return obj;
}
void calc_max_dist(vector<vl>& g, vl& maxi, ll inicio, ll n)
{
    vl v(n, 0);
    vl d(n, INF);

    d[inicio] = 0;
    queue<ll> q;
    q.push(inicio);
    while(!q.empty()){

        ll t = q.front();
        q.pop();
        

        if(!v[t]){
            
            maxi[t] = max(maxi[t], d[t]);
            v[t] = 1;
            for(auto it : g[t]){

                if(!v[it])
                {
                    
                    d[it] = d[t]+1;
                    
                    q.push(it);
                }
            }
        }
    }
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while(cin >> N >> Q){

        ll x, y;
        

        vector<vl> g1(N, vl()), g2(Q, vl());
        for(int i = 0; i < N-1; i++){
            cin >> x >> y; x--; y--;
            g1[x].push_back(y);
            g1[y].push_back(x);
        }
        for(int i = 0; i < Q-1; i++){
            cin >> x >> y; x--; y--;
            g2[x].push_back(y);
            g2[y].push_back(x);
        }
 

        ll ext1_N = get_far(g1, N, 0, 0), ext2_N = get_far(g1, N, ext1_N, 0);
        ll ext1_Q = get_far(g2, Q, 0, 1), ext2_Q = get_far(g2, Q, ext1_Q, 1);

       
        d_Q.assign(Q, 0); d_N.assign(N, 0);

        calc_max_dist(g1, d_N, ext2_N, N);
        calc_max_dist(g1, d_N, ext1_N, N);
        calc_max_dist(g2, d_Q, ext2_Q, Q);
        calc_max_dist(g2, d_Q, ext1_Q, Q);

        //cout << ext1_N << " "<<ext2_Q << endl;
        //cout << dN << " "<< dQ << "\n"; 
        


        ll aux = max(dQ, dN);

        sort(ALL(d_Q)); sort(ALL(d_N));

        

        vl ac (Q, 0);
        for(int i = Q-1; i >= 0; i--)
        {
            ac[i] = d_Q[i];
            if(i != Q-1) ac[i] += ac[i+1];  
        }
        
        ll ans = 0;
        ll p2 = Q-1;
        
        
        for(int i = 0; i < N; i++){
            while(p2 >= 0 && d_Q[p2] + d_N[i] + 1 > aux) p2--;

            if(p2 != Q-1)
                ans += ac[p2+1] + (Q - p2-1)*(d_N[i] + 1);
            //cout<<p2<<"\n";
            ans += aux * (p2+1);
            //cout<<ans<<"*"<<p2<<" "<<ac[p2]<<"\n";
        }


        cout <<fixed << setprecision(3) << (db)ans / (db)(Q * N) << "\n";

    }
   
   
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
