#include <bits/stdc++.h>
using namespace std;
void time()
{
    for(long long k=0;k<100000000;k++)
    {}
}
int main()
{
    cout<<pow(5,20);
	int c[5]={1,5,10,25,50};
	int n;
	while(cin>>n)
	{
		int m[n+1];
		m[0]=1;
		for(int i=1;i<=n+1;i++)m[i]=0;
		for(int j=0;j<5;j++)//intercambiar los for para calcular la cantidad de combinaciones o la minima cantidad de monedas
		{
			for(int i=1;i<=n+1;i++)
			{
				if(i-c[j]>=0)
				{
					m[i]+=m[i-c[j]];
					//m[i]=min(m[i],m[i-c[j]]+1);
				}
			}
			//for(int i=0;i<=n;i++)cout<<m[i]<<" ";
		}
		cout<<m[n]<<endl;
	}

	return 0;
}
