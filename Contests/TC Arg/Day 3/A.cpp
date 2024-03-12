#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef long long ll;

#define rep(i, n) for(int i = 0; i < (int)n; i++)

const int MAX = 2e5;
struct Trie
{
  
  int c = 0;
  vector<vector<int>> N;
  vector<int> S;

  Trie()
  {
    N.assign(MAX, vector<int>(26, 0));
    S.assign(MAX, 0);
    c = 0;
  }

  void add(string s, int a = 1)
  {
    int p = 0; S[p] += a;
    for (char l : s)
    {
      int t = l - 'a';
      if(!N[p][t]) N[p][t] = ++c;
      S[p = N[p][t]] += a;
    }
  }

  bool search(string s, int a = 1)
  {
    int p = 0;
    for ( char l : s)
    {
      int t = l - 'a';
      if(!N[p][t]) return 0;
      p = N[p][t];
    }
    return 1;
  }
};

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  int q;
  cin >> q;

  Trie No, Rev;

  rep(i, q)
  {
    int type;
    string s;
    cin >> type;
    if(type == 1)
    {
      cin >> s;
      No.add(s);
      reverse(s.begin(), s.end());
      Rev.add(s);
    }
    else if(type == 2)
    {
      cin >> s;
      cout << No.search(s) << "\n";
    }
    else{
      swap(No, Rev);
    }
  }
}