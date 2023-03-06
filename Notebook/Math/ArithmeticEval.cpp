#include "../Header.cpp"


ll k, n;
string s;

ll eval(ll l, ll r){
	ll open = 0;
	stack<ll> vals;
	stack<char> ops;

	if(s[l] == '+' || s[l] == '*' || s[r] == '+' || s[r] == '*')return -1;
	if(s[l] == '0' && r-l >= 1 && isdigit(s[l+1]))return -1;

	repx(i, l, r+1){
		if(isdigit(s[i])){
			vals.push((s[i] - '0') % k);
			while(i < r && isdigit(s[i+1])){
				i++;
				vals.top() = (vals.top() * 10 + (s[i] - '0')) % k;
		
				
			}
		}
		else if(s[i] == '(')
		{
			open++;
			ops.push(s[i]);
		}
		else if(s[i] == ')')
		{
			open--;
			if(open < 0) return -1;
			ll in = i-1;
			while(ops.top() != '('){
				ll aux = vals.top();
				vals.pop();
				if(ops.top() == '+'){
					vals.top() = (vals.top() + aux) % k;
				}
				else{
					
					vals.top() = (vals.top() * aux) % k;
				}
				ops.pop();
			}
			ops.pop();
		}
		else{
			// higher precedence first
			while(!ops.empty() && ops.top() == '*'){
				ll aux = vals.top();
				vals.pop();
				vals.top() = (vals.top() * aux) % k;
				ops.pop();
			}
			ops.push(s[i]);
		}
	}
	if(open != 0) return -1;

	while(!ops.empty()){
		ll aux = vals.top();
		vals.pop();
		if(ops.top() == '+'){
			vals.top() = (vals.top() + aux) % k;
		}
		else{
			vals.top() = (vals.top() * aux) % k;
		}
		ops.pop();
	}
	
	return vals.top();
}

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand((unsigned int) time(0));


	cin >> k >> n;
	cin >> s;

	//cout << eval(0, n-1)<<"\n";
	ll ans = 0;
	rep(i, n){
		repx(j, i, n){
			if(eval(i, j) == 0){
				ans++;
				//cout << i << " " << j <<" "<<eval(i,j)<< "\n";
			}
	
		}
	}
	cout << ans << "\n";
	
	cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}