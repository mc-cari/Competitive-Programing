#include "../Header.cpp"

// From CP4: https://github.com/stevenhalim/cpbook-code/blob/master/ch4/traversal/UVa11838.cpp

vl dfs_num, dfs_low, visited; 
vector<vl> g, invg;
void Kosaraju(int u, int pass, vl& S) { // pass = 1 (original), 2 (transpose)
  dfs_num[u] = 1;
  vl &neighbor = (pass == 1) ? g[u] : invg[u]; 
  for (auto it : neighbor)                  
    if (dfs_num[it] == -1)
      Kosaraju(it, pass, S);
  S.push_back(u);
}
//


// -----------------------------------------
// implementation of Tarjan's SCC algorithm
stack<int> St;
int cont, numSCC;

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = cont;    
  cont++;                            
  St.push(u);                                   
  visited[u] = 1;
  for (auto v : g[u]) {
    if (dfs_num[v] == -1)
      tarjanSCC(v);
    if (visited[v])                             
      dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }

  if (dfs_low[u] == dfs_num[u]) {                                  
    while (1) {
      int v = St.top(); St.pop(); visited[v] = 0;

      if (u == v) break;
    }
    ++numSCC;  
  }
}


int main() {

    int n, m; cin >> n >> m;
    vector<vl> g(n);
    while(m--) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
    }
    // run Tarjan's SCC 
    dfs_num.assign(n, 0); dfs_low.assign(n, 0); visited.assign(n, 0);
    while (!St.empty()) St.pop();
    cont = numSCC = 0;
    for (int u = 0; u < n; ++u)
     if (dfs_num[u] == -1)
       tarjanSCC(u);


    //Kosaraju's SCC

    vl S;
    dfs_num.assign(n, -1);
    for (int u = 0; u < n; ++u)
        if (dfs_num[u] == -1)
            Kosaraju(u, 1, S);
    int numSCC = 0; 
    dfs_num.assign(n, -1);
    for (int i = n-1; i >= 0; --i){
        vl comp;
        if (dfs_num[S[i]] == -1)
            numSCC++, Kosaraju(S[i], 2, comp);             // on transposed graph
    }

    return 0;
}