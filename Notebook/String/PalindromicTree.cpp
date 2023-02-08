#include "../Header.cpp"
  
#define MAXN 2000005
ll M = 51123987;
struct Node 
{ 
    // store start and end indexes of current 
    // Node inclusively 
    // only for first ocurrence
    ll start, end; 
  
    // stores length of substring 
    ll length; 
  
    // stores insertion Node for all characters a-z 
    ll insertEdg[26]; 
  
    // stores the Maximum Palindromic Suffix Node for 
    // the current Node 
    ll suffixEdg; 
    
    ll depht;
}; 
  
// two special dummy Nodes as explained above 
Node root1, root2; 
  
// stores Node information for constant time access 
Node tree[MAXN]; 
  
// Keeps track the current Node while insertion 
ll currNode; 
string s; 
ll ptr; 
  
void insert(ll idx) 
{ 
//STEP 1// 
  
    /* search for Node X such that s[idx] X S[idx] 
       is maximum palindrome ending at position idx 
       iterate down the suffix link of currNode to 
       find X */
    ll tmp = currNode; 
    while (true) 
    { 
        ll curLength = tree[tmp].length; 
        if (idx - curLength >= 1 and s[idx] == s[idx-curLength-1]) 
            break; 
        tmp = tree[tmp].suffixEdg; 
    } 
  
    /* Now we have found X .... 
     * X = string at Node tmp 
     * Check : if s[idx] X s[idx] already exists or not*/
    if(tree[tmp].insertEdg[s[idx]-'a'] != 0) 
    { 
        // s[idx] X s[idx] already exists in the tree 
        currNode = tree[tmp].insertEdg[s[idx]-'a']; 
        return; 
    } 
  
    // creating new Node 
    ptr++; 
  
    // making new Node as child of X with 
    // weight as s[idx] 
    tree[tmp].insertEdg[s[idx]-'a'] = ptr; 
  
    // calculating length of new Node 
    tree[ptr].length = tree[tmp].length + 2; 
  
    // updating end point for new Node 
    tree[ptr].end = idx; 
  
    // updating the start for new Node 
    tree[ptr].start = idx - tree[ptr].length + 1; 
 
  
  
//STEP 2// 
  
    /* Setting the suffix edge for the newly created 
       Node tree[ptr]. Finding some String Y such that 
       s[idx] + Y + s[idx] is longest possible 
       palindromic suffix for newly created Node.*/
  
    tmp = tree[tmp].suffixEdg; 
  
    // making new Node as current Node 
    currNode = ptr; 
    if (tree[currNode].length == 1) 
    { 
        // if new palindrome's length is 1 
        // making its suffix link to be null string 
        tree[currNode].suffixEdg = 2; 
        tree[currNode].depht = 1;
        return; 
    } 
    while (true) 
    { 
        ll curLength = tree[tmp].length; 
        if (idx-curLength >= 1 and s[idx] == s[idx-curLength-1]) 
            break; 
        tmp = tree[tmp].suffixEdg; 
    } 
  
    // Now we have found string Y 
    // linking current Nodes suffix link with s[idx]+Y+s[idx] 
    tree[currNode].suffixEdg = tree[tmp].insertEdg[s[idx]-'a'];
    tree[currNode].depht = tree[tree[tmp].insertEdg[s[idx]-'a']].depht + 1; 
 
} 
// para ir al revez currNode = 1, reverse(s)
// para un string nuevo, devolver currNode o currNode = 1

// driver program 
int main() 
{ 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // initializing the tree 
    root1.length = -1; 
    root1.suffixEdg = 1; 
    root2.length = 0; 
    root2.suffixEdg = 1; 
    root1.depht = 0;
    root2.depht = 0;
  
    tree[1] = root1; 
    tree[2] = root2; 
    ptr = 2; 
    currNode = 1; 
    ll l;
    cin >> l;
    cin >> s;
    l = s.length();
    cout<<l<<endl;
    vl sums(l+1, 0);
    ll ans = 0;

    for (ll i=0; i<l; i++){ 
        insert(i); 
        ll nod = currNode, depht = 0;
        while(tree[nod].length > 0)
        {
          nod = tree[nod].suffixEdg;
          depht++;
        }
        nod = currNode;
        sums[i+1]=(depht + sums[i])%M;
        depht--;
        while(tree[nod].length > 1)
        {
          ans += (depht + sums[i] - sums[i - tree[nod].length + 1])%M;
          ans %= M;
          
          nod = tree[nod].suffixEdg;
          depht--;
        }
        
    }
    cout<<ans<<"\n";

    // printing all of its distinct palindromic 
    // substring 
    cout << "All distinct palindromic substring for "
         << s << " : \n"; 
    for (int i=3; i<=ptr; i++) 
    { 
        cout << i-2 << ") "; 
        for (int j=tree[i].start; j<=tree[i].end; j++) 
            cout << s[j]; 
        cout << endl; 
    }
  
  
  cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
  return 0;
}