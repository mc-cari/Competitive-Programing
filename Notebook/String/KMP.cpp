#include "../Header.cpp"


// FROM:
//https://github.com/PabloMessina/Competitive-Programming-Material/blob/master/Strings/KMP.cpp

// Build longest proper prefix/suffix array (lps) for pattern
// lps[i] = length of the longest proper prefix which is also suffix in pattern[0 .. i]
void init_lps(string& s, int lps[]) {
    int n = s.size();
    lps[0] = 0; // base case: no proper prefix/suffix for pattern[0 .. 0] (length 1)
    repx(j, 1, n) { // for each s[0 .. j]
        int i = lps[j-1]; // i points to the char next to lps of previous iteration
        while (s[i] != s[j] and i > 0) i = lps[i-1];
        lps[j] = s[i] == s[j] ? i+1 : 0;

        //optimization to reutilice the lps in O(n)
        if(i > 0 && s[i] == s[lps[i-1]] && lps[i-1] != 0) lps[i-1] = lps[lps[i-1]-1]; 
    }
}

// Count number of matches of pattern string in target string using KMP algorithm
int kmp(string& s, string& t) {
    int n = s.size(), m = t.size();
    int lps[n];
    init_lps(s, lps); // build lps array
    int matches = 0;
    int i = 0; // i tracks current char in pattern to compare
    rep(j, m) { // j tracks each char in target to compare
        // try to keep prefix before i as long as possible while ensuring i matches j        
        while (s[i] != t[j] && i > 0) i = lps[i-1];
        if (s[i] == t[j]) {
            if (++i == n) { // we matched the whole pattern
                i = lps[n-1]; // shift the pattern so that the longest proper prefix/suffix pair is aligned

				matches++;
								
            }
        }
    }
    return matches;
}

int main() { // usage
    string target, pattern;
    while (true) {
        cin >> target >> pattern;
        cout << kmp(pattern, target) << " matches\n";
    }
    return 0;
}