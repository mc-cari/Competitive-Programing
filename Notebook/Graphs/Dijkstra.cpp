#include "../Header.cpp"

int main()
{
	vl d(v, INF);
	priority_queue<pll, vp, greater<pll> > q;
	ll s, t;
	q.push({0, s});
	d[s] = 0;	
	while(!q.empty()){
			ll w, u;
			tie(w, u) = q.top();
			q.pop();
			if(w > d[u]) continue;
			for(auto it : g[u]){
					if(d[it.second] > w + it.first){
							d[it.second] = w + it.first;
							q.push({d[it.second], it.second});
					}
			}
	}
}
