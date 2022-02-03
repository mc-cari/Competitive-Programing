include <iostream>
using namespace std;
int Array[52];
int sum=0;
long long fibo(long long a)
{
    sum++;
    for (int i=2;i<=a;i++)
    {
      Array[i]=Array[i-1]+Array[i-2];
    }
    return Array[a];
}

int main() {
    Array[0]=0;
    Array[1]=1;
    cout<<fibo(5);
    cout<<endl<<sum;
    return 0;
}
