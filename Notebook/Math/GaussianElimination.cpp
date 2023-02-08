#include "../Header.cpp"

const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
	
	ll n = 2;

	vector<vl>g (2, vl(3, 0));

	g[0][0] = 1;
	g[1][1] = 1;
	g[0][2] = 1;
	g[1][2] = 2;

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

	for(int i = 0; i < n-1; i++)
		cout << vals[i] << " ";

	cout << endl;

	for(int i = 0; i < n; i++)
	{

		for(int j = 0; j < n+1; j++)
			cout << g[i][j] << " ";
		cout << endl;
		
	}

}