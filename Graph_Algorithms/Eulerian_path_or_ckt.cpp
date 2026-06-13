// Section: Graph Algorithms
// Topic:   Eulerian path or ckt

class Euleriandirected {
    int V,M;
    vector<vector<int>> adj;
    vector<int> in_deg, out_deg;
    int cnt=0;
public:
    Euleriandirected(int V,int M) {
        this->V = V;
        this->M=M;
        adj.resize(V);
        in_deg.resize(V, 0);
        out_deg.resize(V, 0);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        out_deg[u]++;
        in_deg[v]++;
    }
    int getEulerType() {
        int start_nodes = 0, end_nodes = 0;
        for (int i = 0; i < V; ++i) {
            if (out_deg[i] - in_deg[i] == 1) start_nodes++;
            else if (in_deg[i] - out_deg[i] == 1) end_nodes++;
            else if (in_deg[i] != out_deg[i]) return 0;
        }
        if (start_nodes == 0 && end_nodes == 0) return 2; // Eulerian Circuit
        if (start_nodes == 1 && end_nodes == 1) return 1; // Eulerian Path
        return 0;
    }
    void findEulerPathOrCircuit() {
        int type = getEulerType();
        if (type == 0) {
            cout << "No\n";
            return;
        }
        int start = 0;
        if (type == 1) {
            for (int i = 0; i < V; ++i) {
                if (out_deg[i] - in_deg[i] == 1) {
                    start = i;
                    break;
                }
            }
        } else {
            for (int i = 0; i < V; ++i) {
                if (!adj[i].empty()) {
                    start = i;
                    break;
                }
            }
        }
        vector<int> path;
        hierholzer(start, path);
        reverse(path.begin(), path.end());
      if(path.size()!=M+1){
        cout<<"Graph not connected\n";
        return;
      }
        cout<<"Yes\n";
        for (int v : path)
            cout << v << " ";
          cout << endl;
    }
    void hierholzer(int v, vector<int>& path) {
        while (!adj[v].empty()) {
            int u = adj[v].back();
            adj[v].pop_back();
            hierholzer(u, path);
        }
        path.push_back(v);
    }
};

struct Edge {
    int to;
    int id;
};
class EulerianUndirected {
    int V, E;
    vector<vector<Edge>> adj;
    vector<bool> used;
    vector<int> deg;
    vector<int>cur;
public:
    EulerianUndirected(int n, int m) {
        V = n;
        E = m;
        adj.resize(n);
        used.resize(m, false);
        deg.resize(n, 0);
        cur.resize(n,0);
    }
    void addEdge(int u, int v, int id) {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
        deg[u]++;
        deg[v]++;
    }
    int getEulerType() {
        int odd = 0;
        for (int i = 0; i < V; ++i)
            if (deg[i] % 2 != 0) odd++;
        if (odd == 0) return 2;     // Eulerian Circuit
        if (odd == 2) return 1;     // Eulerian Path
        return 0;                   // No Eulerian Trail
    }
    void findEuler() {
        int type = getEulerType();
        if (type == 0||type==1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        int start = 0;
        vector<int> path;
        dfs(start, path);
        if (path.size() != E + 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        for (int v : path) cout << v+1 << " ";
        cout << "\n";
        // for (int e : edge_path) cout << e << " ";
        // cout << "\n";
    }
    void dfs(int v, vector<int>& path) {
       while(cur[v]<(int)adj[v].size()){
        auto e=adj[v][cur[v]++];
        if(used[e.id])continue;
        used[e.id]=true;
        dfs(e.to,path);
       }
       path.push_back(v);
    }
};

void solve(){

    int n,m;
    cin>>n>>m;
    EulerianUndirected res(n,m);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        --u,--v;
        res.addEdge(u,v,i);
    }
    res.findEuler();
}
