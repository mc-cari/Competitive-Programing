#include "../Header.cpp"

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	vector<vl>g;
	ll n;

    // g: rows: equations, columns: x_1 * p_1 + x_2 * p_2 + x_3 * p_3 = y
	for(int i = 0; i < n-2; i++)
	{
		
		for(int z = i+1; z < n-1; z++)
		{
			db mul = g[z][i] / g[i][i];
			for(int j = 0; j < n; j++)
				g[z][j] -= mul * g[i][j];
			
		}
		
	}
	vector<db> vals(n, 0);

	for(int i = n-2; i >= 0; i--)
	{
		db sum = g[i][n-1];
		for(int j = i+1; j < n-1; j++)
			
			sum -= g[i][j] * vals[j];
		
		sum /= g[i][i];
		vals[i] = sum;
	}


}