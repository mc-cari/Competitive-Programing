#include "../Header.cpp"

//https://www.geeksforgeeks.org/determinant-of-a-matrix/
 
// Dimension of input square matrix
#define N 4
 
// Function to get cofactor of mat[p][q] in temp[][]. n is
// current dimension of mat[][]
void getCofactor(int mat[N][N], int temp[N][N], int p,
                 int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
/* Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. */
int determinantOfMatrix(int mat[N][N], int n)
{
    int D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return mat[0][0];
 
    int temp[N][N]; // To store cofactors
 
    int sign = 1; // To store sign multiplier
 
    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f]
             * determinantOfMatrix(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}
 
/* function for displaying the matrix */
void display(int mat[N][N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout <<"  " <<  mat[i][j];
        cout <<"n";
    }
}
 
// Driver program to test above functions
int main()
{
    /* int mat[N][N] = {{6, 1, 1},
                     {4, -2, 5},
                     {2, 8, 7}}; */
 
    int mat[N][N] = { { 1, 0, 2, -1 },
                      { 3, 0, 0, 5 },
                      { 2, 1, 4, -3 },
                      { 1, 0, 5, 0 } };

    int T[N][N]; //Tutte matrix
    //range of matrix(number of pivots) is # different matching maximum
    ll n, m;
    for(int i = 0; i < m; i++)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        mat[x][y] = -1;//-w; 
        mat[y][x] = -1;//-w;
        mat[x][x] += 1;//w;
        mat[y][y] += 1;//w;

        T[x][x] = 0;
        T[x][y] = rand() % 1e9+7;
        T[y][x] = -T[x][y];

    }

    // O(N^3)
    cout <<"Number of spanning trees/weight sum of spanning tree : " << determinantOfMatrix(mat, N-1);

    cout <<"Number of spanning forest with i in one component and j in the other : " << determinantOfMatrix(mat, N-i -j);//delete i/t row and column
    
    if(determinantOfMatrix(T, N) == 0)
        cout <<"Does not exist a maximum matching in the general graph (need more verify)";
    else
        cout <<"Does exist perfect matching";
    cout <<"Number of spanning trees/weight sum of spanning tree : " << determinantOfMatrix(T, N);
    return 0;
}
 