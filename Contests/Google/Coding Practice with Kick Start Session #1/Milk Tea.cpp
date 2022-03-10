    #include<bits/stdc++.h>
    #pragma GCC optimize("Ofast")
    using namespace std;
    typedef long long ll;
    typedef unsigned long long ull;
    typedef vector<ll> vl;
    typedef pair<ll,ll> pll;
    typedef vector<pll> vp;
    typedef double db;
    #define INF 1e17
    #define EPS 1e-7
    #define ALL(x) x.begin() , x.end()
    #define ALLR(x) x.rbegin() , x.rend()
    #define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
    #define PI acos(-1.0)



    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);

        ll t;
        cin >> t;
        for(int T = 1; T <= t; T++)
        {
            ll n, m, p;
            string s;
            unordered_map< ll, ll> mp;
            
            cin >> n >> m >> p;
            vl cont(p, 0), cont2(p, 0);
            

            for(int i = 0; i < n; i++)
            {
                cin >> s;
                for(int j = 0; j < p; j++)
                    if(s[j] == '1') cont[j]++;
            }
            vp ord;
            vl nex(p, 0);
            for(int i = 0; i < p; i++)
                ord.push_back({abs(cont[i] - (n - cont[i])), i});
            sort(ALLR(ord));
            for(int i = 0; i < p; i++)
            {
                nex[ord[i].second] = i;
                cont2[i] = cont[ord[i].second];
            }
            swap(cont, cont2);
                
            for(int j = 0; j < m; j++)
            {
                ll x = 0;
                cin >> s;

                for(int i = 0; i < p; i++)
                    if(s[i] == '1')
                        x += (1 << nex[i]);

                mp[x] = 1;
            }

            
            ll mini2 = INF;
            for(int i = 0; i < (1 << p); i++)
            {
                if(mp[i])continue;
                ll aux = 0;
                for(int j = 0; j < p; j++)
                {
                    if(i & (1 << j))
                        aux += n - cont[j];
                    else
                        aux += cont[j];
                }
                mini2 = min(mini2, aux);
            }
            //cout << "Case #" << T << ": " << mini2 << "\n";
            
        
            ll mini = 0, obj = 0, ref;
            for(int i = 0; i < p; i++)
            {
                if(cont[i] > n - cont[i])
                {
                    obj += (1 << i);
                    mini += n - cont[i];
                }
                else mini += cont[i];
            }
            ref = mini;
            if(mp[obj]) mini = INF;
            vector<string> ss(p-1, string(p, '1'));

            priority_queue<pair<ll, string>, vector<pair<ll, string>>, greater<pair<ll, string>> > q;

            for(int i = 0; i < p-1; i++)
            {
                ll x = ref;
                for(int j = 0; j < i + 1; j++)
                {
                    ss[i][p - j - 1] = '0';
                    x += abs(cont[j] - (n - cont[j]));
                }
                //cout << x << "\n";
                q.push({x, ss[i]});
            }

            ll in = 0;
            while(in < 200 && !q.empty())
            {
                in++;
                ll x = q.top().first;
                string b = q.top().second;
                q.pop();

                ll ver = 0;
                for(int i = 0; i < p ; i++)
                {
                    if(b[i] == '1' && ((1 << i) & obj))
                        ver += (1 << i);
                    if(b[i] == '0' && !((1 << i) & obj))
                        ver += (1 << i);
                }
                    

                if(!mp[ver]) mini = min(mini, x);

                if(prev_permutation(ALL(b)))
                {
                    ll y = ref;
                    for(int i = 0; i < p; i++)
                    {
                        if(b[i] == '0')
                            y += abs(cont[i] - (n - cont[i]));
                    }
                    //cout << y << " " << b << "\n";
                    q.push({y, b});
                }
            }
        }

        cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
        return 0;
        
    }