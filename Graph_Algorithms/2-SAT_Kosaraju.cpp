// Section: Graph Algorithms
// Topic:   2-SAT (Kosaraju)

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg;
    vector<int> vis, comp, ord, val;
    TwoSAT(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(2 * n, {}); rg.assign(2 * n, {});
        vis.assign(2 * n, 0); comp.assign(2 * n, -1);
        ord.clear(); val.assign(n, 0);
    }
    int lit(int x, bool isTrue) { return 2 * x ^ (!isTrue); } // x in [0..n-1]
    int neg(int v) { return v ^ 1; }
    void addEdge(int u, int v) { g[u].push_back(v); rg[v].push_back(u); }
    // (x=av) => (y=bv)
    void addImp(int x, bool av, int y, bool bv) { addEdge(lit(x, av), lit(y, bv)); }
    // (x=av) OR (y=bv)
    void addOr(int x, bool av, int y, bool bv) {
        addImp(x, !av, y, bv);
        addImp(y, !bv, x, av);
    }
    // force (x=av)
    void forceVar(int x, bool av) { addImp(x, !av, x, av); }
    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
        ord.push_back(u);
    }
    void dfs2(int u, int c) {
        comp[u] = c;
        for (int v : rg[u]) if (comp[v] == -1) dfs2(v, c);
    }
    // call solve(); false => impossible, true => val[i] in {0,1}
    bool solve() {
        for (int i = 0; i < 2 * n; i++) if (!vis[i]) dfs1(i);
        reverse(ord.begin(), ord.end());
        int cc = 0;
        for (int u : ord) if (comp[u] == -1) dfs2(u, cc++);
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) return false;
            val[i] = (comp[2 * i] > comp[2 * i + 1]);
        }
        return true;
    }
};
/* usage:
TwoSAT sat(n);
sat.addOr(a,1,b,0);    // (xa=true) OR (xb=false)
sat.addImp(a,1,b,1);   // (xa=true) => (xb=true)
sat.forceVar(c,0);     // xc=false
if (sat.solve()) auto ans = sat.val;
*/
