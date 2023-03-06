#include "../Header.cpp"

#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
 
namespace Simplex {
vector<int> X,Y;
vector<vector<db> > A;
vector<db> b,c;
db z;
int n,m;
void pivot(int x,int y){
	swap(X[y],Y[x]);
	b[x]/=A[x][y];
	fore(i,0,m)if(i!=y)A[x][i]/=A[x][y];
	A[x][y]=1/A[x][y];
	fore(i,0,n)if(i!=x&&abs(A[i][y])>EPS){
		b[i]-=A[i][y]*b[x];
		fore(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
		A[i][y]=-A[i][y]*A[x][y];
	}
	z+=c[y]*b[x];
	fore(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
	c[y]=-c[y]*A[x][y];
}
pair<db,vector<db> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
		vector<vector<db> > _A, vector<db> _b, vector<db> _c){
	// returns pair (maximum value, solution vector)
	A=_A;b=_b;c=_c;
	n=b.size();m=c.size();z=0.;
	X=vector<int>(m);Y=vector<int>(n);
	fore(i,0,m)X[i]=i;
	fore(i,0,n)Y[i]=i+m;
	while(1){
		int x=-1,y=-1;
		db mn=-EPS;
		fore(i,0,n)if(b[i]<mn)mn=b[i],x=i;
		if(x<0)break;
		fore(i,0,m)if(A[x][i]<-EPS){y=i;break;}
        if(y<0) return(make_pair(-1, b));
		assert(y>=0); // no solution to Ax<=b
		pivot(x,y);
	}
	while(1){
		db mx=EPS;
		int x=-1,y=-1;
		fore(i,0,m)if(c[i]>mx)mx=c[i],y=i;
		if(y<0)break;
		db mn=INF;
		fore(i,0,n)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
		assert(x>=0); // c^T x is unbounded
		pivot(x,y);
	}
	vector<db> r(m);
	fore(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
	return {z,r};
}
}
 
int main(){
	ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll n, k, x;
    db y;
    cin >> n >> k >> x;
 
    vector<db> b, c;
    vector<vector<db> > A;
 
    for(int i = 0; i < n; i++)
    {
        cin >> y;
        c.push_back(y);
    }
 
    vector<db>aux(n, 0);
    for(int i = 0; i < k; i++)aux[i] = -1;
    A.push_back(aux);
    b.push_back(-1.);
 
    for(int i = k; i < n; i++)
    {
        aux[i - k] = 0;
        aux[i] = -1;
        A.push_back(aux);
        b.push_back(-1);
    }
    aux.assign(n, 0);
    for(int i = 0; i < n; i++)
    {
        aux[i] = 1;
        A.push_back(aux);
        b.push_back(1);
        aux[i] = 0;
    }
    aux.assign(n, 1);
    A.push_back(aux);
    b.push_back(x);
    ll in = 0;
    /*for(auto it : A)
    {
        for(auto it2: it)cout<<it2<<" ";
        cout<<"  "<<b[in];
        in++;
        cout<<"*\n";
    }*/
 
    db mx = Simplex::simplex(A,b,c).first;
    cout<<(long long)mx<<"\n";
 
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}