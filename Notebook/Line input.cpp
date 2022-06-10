#include "Header.cpp"

int main()
{
    // save strings
    string line, token;
    getline(cin, line);
    stringstream ss(line);
    while(ss >> token)
    {
        cout << token << "\n";
    }
	return 0;
}
