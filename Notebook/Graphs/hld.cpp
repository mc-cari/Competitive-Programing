#include "../common.h"

#define NOMAIN_SEGTREELAZY
#include "../ds/segtreelazy.cpp"

struct Hld {
    vector<int> parent, heavy, depth, pos, top;

    Hld() {}
    void init(vector<vector<int>>& G) {
        int N = G.size();
        parent.resize(N), heavy.resize(N), depth.resize(N), pos.resize(N),
            top.resize(N);
        depth[0] = -1, dfs(G, 0);
        int t = 0;
        rep(i, N) if (heavy[parent[i]] != i) {
            int j = i;
            while (j != -1) {
                top[j] = i, pos[j] = t++;
                j = heavy[j];
            }
        }
    }

    int dfs(vector<vector<int>>& G, int i) {
        int w = 1, mw = 0;
        depth[i] = depth[parent[i]] + 1, heavy[i] = -1;
        for (int c : G[i]) {
            if (c == parent[i]) continue;
            parent[c] = i;
            int sw = dfs(G, c);
            if (sw > mw) heavy[i] = c, mw = sw;
            w += sw;
        }
        return w;
    }

    template <class OP>
    void path(int u, int v, OP op) {
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) swap(u, v);
            op(pos[top[v]], pos[v]);
            v = parent[top[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v]);  // value on vertex
        // op(pos[u]+1, pos[v]); // value on path
    }

    // segment tree
    template <class T, class S>
    void update(S& seg, int i, T val) {
        seg.update(pos[i], val);
    }

    // segment tree lazy
    template <class T, class S>
    void update(S& seg, int u, int v, T val) {
        path(u, v, [&](int l, int r) { seg.update(l, r, val); });
    }

    template <class T, class S>
    T query(S& seg, int u, int v) {
        T ans = 0;
        path(u, v, [&](int l, int r) { ans += seg.query(l, r); });  // query op
        return ans;
    }
};

#ifndef NOMAIN_HLD

Hld hld;
Stl<ll> seg;

void que(int u, int v, ll ex) {
    ll out = hld.query<ll>(seg, u - 1, v - 1);
    ll out2 = hld.query<ll>(seg, v - 1, u - 1);
    assert(out == out2);
    cerr << "query for (" << u << ", " << v << ") = " << out << endl;
    if (out != ex) {
        cerr << "expected " << ex << ", got " << out << endl;
        assert(out == ex);
    }
}

void upd(int u, int v, int val) {
    cerr << "update for (" << u << ", " << v << ") with " << val << endl;
    hld.update(seg, u - 1, v - 1, val);
}

int main() {
    vector<pair<int, int>> conns = {
        {1, 2},   {1, 3},   {1, 4},  {2, 12}, {12, 13}, {12, 14},
        {14, 15}, {3, 5},   {3, 6},  {6, 7},  {7, 8},   {8, 9},
        {8, 10},  {10, 11}, {8, 18}, {4, 16}, {4, 17}};
    vector<vector<int>> G(18);
    for (auto edge : conns) {
        G[edge.first - 1].push_back(edge.second - 1);
        G[edge.second - 1].push_back(edge.first - 1);
    }

    // hld
    //
    //      1
    //    / | \ 
    //   2  3   4
    //  /  / \  | \ 
    // 12  5  6 16 17
    // | \     \ 
    // 13 14    7
    //    |     |
    //    15    8
    //        / | \ 
    //       9 10  18
    //          |
    //         11
    hld.init(G);
    seg.resize(G.size());
    que(11, 5, 0);
    que(13, 12, 0);
    que(8, 8, 0);
    que(4, 16, 0);
    upd(14, 3, 1);
    que(2, 5, 3);
    que(12, 15, 2);
    que(13, 17, 3);
    upd(9, 11, 10);
    que(10, 7, 20);
    que(11, 7, 30);
    upd(8, 16, -1);
    que(9, 18, 19);
    que(9, 5, 17);
    que(8, 8, 9);
    que(17, 17, 0);
    upd(17, 16, 10);
    que(16, 11, 2 + 30 - 7 + 20);
}

#endif
