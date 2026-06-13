// Section: Graph Algorithms
// Topic:   Centroid Decomposition

const int MAXN = 1e5+5;
vector<int> adj[MAXN];
bool dead[MAXN];         // Marks removed node, centroid found
int sub[MAXN];           // Subtree sizes
char ans[MAXN];          // Color for each node
bool possible = true;    // check possible assignment

// Compute subtree sizes for the current subtree (ignoring 'dead' nodes)
int compute_subtree(int u, int parent) {
    sub[u] = 1;
    for (int v : adj[u]) {
        if (v != parent && !dead[v]) {
            sub[u] += compute_subtree(v, u);
        }
    }
    return sub[u];
}
// Centroid of subtree with root 'u' given total size
int find_centroid(int u, int parent, int total) {
    for (int v : adj[u]) {
        if (v != parent && !dead[v] && sub[v] > total / 2)
            return find_centroid(v, u, total);
    }
    return u;
}
// Perform centroid decomposition and color the centroid with 'col'
void decompose(int u, char col) {
    if (col > 'Z') {     // impossible If col exceed 'Z'
        possible = false;
        return;
    }
    int total = compute_subtree(u, -1);
    int cent = find_centroid(u, -1, total);
    ans[cent] = col;      
    dead[cent] = true;
    for (int v : adj[cent]) {
        if (!dead[v]) decompose(v, col + 1);
    }
}
