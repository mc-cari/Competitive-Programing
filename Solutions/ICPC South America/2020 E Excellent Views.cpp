#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

typedef int ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef vector<pll> vp;
typedef long double db;
#define INF 1e5
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0)

//https://codeforces.com/gym/103185/problem/E


int main(){
	
	int n;
	cin>>n;

	vector<ii> lista(n);
	vector<int> res(n, 0);
	vector<int> key(n);
	set<int> check;
	
	for(int i = 0; i<n; i++){
		cin>>lista[i].first;
		lista[i].second = i;
		key[i] = lista[i].first;
	}
	
	sort(lista.begin(), lista.end(), greater<ii>());

	vp q;
    for(int i = 0; i < n; i++)
    {
        q.push_back({i, 0});
    }
	for(int i = 0; i<n; i++){
		
		int indice = lista[i].second;
        int l = -1, r = -1;
        
        if(!check.empty()){
            if(check.lower_bound(indice) != check.end())r = *check.lower_bound(indice);

            if(check.lower_bound(indice) != check.begin())l = *prev(check.lower_bound(indice));
        }
		
        if(l == -1)
        {
            if(indice != 0)
            {
                q.push_back({0, -1});
                q.push_back({indice - 1, 1});
            }
        }
        else
        {
            ll aux = indice - l, dis = aux/2;
            if(aux%2 == 0)dis--;
            if(dis != 0)
            {
                q.push_back({indice - dis, -1});
                q.push_back({indice - 1, 1});
            }
        }

        if(r == -1)
        {
            if(indice != n-1)
            {
                q.push_back({indice + 1, -1});
                q.push_back({n - 1, 1});
            }
        }
        else
        {
            ll aux = r - indice, dis = aux/2;
            if(aux%2 == 0)dis--;
            if(dis != 0)
            {
                q.push_back({indice + 1, -1});
                q.push_back({indice + dis, 1});
            }
        }
		
		check.insert(indice);
	}
    sort(ALL(q));
    ll acum = 0;
	for(auto it : q)
    {
        if(it.second == 0)res[it.first] += acum;
        else
        {
            acum -= it.second;
        }
    }
	for(int i = 0; i<n; i++){
		cout<<res[i];
        if(i < n-1)cout<<" ";
        else cout << "\n";
	}
    return 0;
}
