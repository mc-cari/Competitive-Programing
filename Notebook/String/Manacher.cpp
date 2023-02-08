#include "../Header.cpp"

vl manacher(string& s)
{
    int n = s.size();
    // string con # entre medio (2n - 1)
    vl lps(n);
    int l = 0, r = 0, c = 0;
    rep(i, n)
    {
        int j = l+(r-i);
        lps[i] = min(r-i, (int)lps[j]);
        while(i - lps[i] >= 0 && i+lps[i] < n &&
                s[i-lps[i]] == s[i+lps[i]]) lps[i]++;
        
        // acutalizar l, r
        if(r < i + lps[i])
        {
            l = i - lps[i];
            r = i + lps[i];
        }
    }
    // returns total size for each index
    return lps;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll n = 5;
  string s = "aaaaa", s2 = "a#a#a#a#a";

1
2
3
2
1

0
1
2
2
1

  // d1 -> number of expansions
  vector<int> d1(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
      while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
          k++;
      }
      d1[i] = k--;
      if (i + k > r) {
          l = i - k;
          r = i + k;
      }
  }
  // evens, start at index 1, right -> aaAa
  vector<int> d2(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
      int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
      while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
          k++;
      }
      d2[i] = k--;
      if (i + k > r) {
          l = i - k - 1;
          r = i + k ;
      }
  }
  for(auto it : d1)cout<<it<<"\n";
  cout<<"\n";
  for(auto it : d2)cout<<it<<"\n";
  cout<<"\n";
  //vl t = manacher(s2);
  //for(auto it : t)cout<<it<<"\n";
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
