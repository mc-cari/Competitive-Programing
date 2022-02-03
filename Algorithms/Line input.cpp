#include<bits/stdc++.h>
using namespace std;
int main()
{
    //entrega strings
    string line, token;
    getline(cin, line);
    stringstream ss(line);
    while(ss >> token)
    {
        cout << token << "\n";
    }
	return 0;
}
