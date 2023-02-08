#include "../Header.cpp"
int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
  ll n;
	cin >> n;

  vl c(n);
  // next value with lower/grater value
  // right greater, left greater, right lower, left lower
  vl Rg(n, n), Lg(n, -1), Rl(n, n), Ll(n, -1);

  rep(i, n){
    cin >> c[i];
  }
  
  stack<ll> Sg, Sl;
  rep(i, n){
    while(!Sg.empty() && c[Sg.top()] < c[i]){
      Rg[Sg.top()] = i;
      Sg.pop();
    }
    Sg.push(i);

    while(!Sl.empty() && c[Sl.top()] > c[i]){
      Rl[Sl.top()] = i;
      Sl.pop();
    }
    Sl.push(i);
  }
  while(!Sg.empty()) Sg.pop();
  while(!Sl.empty()) Sl.pop();

  for(int i = n-1; i >= 0; i--){
    while(!Sg.empty() && c[Sg.top()] <= c[i]){
      Lg[Sg.top()] = i;
      Sg.pop();
    }
    Sg.push(i);

    while(!Sl.empty() && c[Sl.top()] > c[i]){
      Ll[Sl.top()] = i;
      Sl.pop();
    }
    Sl.push(i);
  }
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}