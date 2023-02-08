#include "Header.cpp"

int main()
{
    // save strings separated by space in a line
    string line, token;
    getline(cin, line);
    stringstream ss(line);
    while(ss >> token)
    {
        cout << token << "\n";
    }
	return 0;
}
