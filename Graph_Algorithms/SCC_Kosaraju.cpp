// Section: Graph Algorithms
// Topic:   SCC (Kosaraju)

struct SCC {
    int n, cc = 0;
    vector<vector<int>> g, rg, dag;
    vector<int> comp, vis, ord;
    SCC(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n, {}); rg.assign(n, {});
        comp.assign(n, -1); vis.assign(n, 0); ord.clear();
        dag.clear(); cc = 0;
    }
    void addEdge(int u, int v) { g[u].push_back(v); rg[v].push_back(u); }
    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        ord.push_back(u);
    }
    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : rg[u]) if (comp[v] == -1) dfs2(v, c);
    }
    // call build(); then comp[u] gives component id [0..cc-1], cc = #SCC
    int build() {
        for (int i = 0; i < n; i++) if (!vis[i]) dfs1(i);
        reverse(ord.begin(), ord.end());
        for (int u : ord) if (comp[u] == -1) dfs2(u, cc++);
        dag.assign(cc, {});
        for (int u = 0; u < n; u++) for (int v : g[u])
            if (comp[u] != comp[v]) dag[comp[u]].push_back(comp[v]);
        for (auto &vec : dag) {
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
        }
        return cc;
    }
};
