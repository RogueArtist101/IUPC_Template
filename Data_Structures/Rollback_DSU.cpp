// Section: Data Structures
// Topic:   Rollback DSU

struct RollbackDSU {
    vector<int> parent, sz;
    stack<pair<int,int>> history;
    int components;
    RollbackDSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }
    int find(int x) {
        while (x != parent[x]) x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            history.push({-1, -1});
            return false;
        }
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        history.push({b, a});
        components--;
        return true;
    }
    void rollback() {
        auto p = history.top();
        int b=p.first,a=p.second;
        history.pop();
        if (b == -1) return;
        parent[b] = b;
        sz[a] -= sz[b];
        components++;
    }
};
const int N=100002;
map<pair<int,int>,int>last;
vector<pair<int,int>>seg[4*N];
int ans[N];
void update(int nd,int s,int e,int l,int r,pair<int,int>&p){
  if(s>r||e<l)return;
  if(l<=s&&r>=e){
    seg[nd].pb(p);
    return;
  }
  int mid=(s+e)/2;
  update(2*nd+1,s,mid,l,r,p);
  update(2*nd+2,mid+1,e,l,r,p);
}

void dfs(int nd,int s,int e,RollbackDSU &dsu){
  int sz=dsu.history.size();
  for(int i=0;i<seg[nd].size();i++)dsu.unite(seg[nd][i].first,seg[nd][i].second);
  if(s==e){
    ans[s]=dsu.components;
  }
  else{
    int mid=(s+e)/2;
    dfs(2*nd+1,s,mid,dsu);
    dfs(2*nd+2,mid+1,e,dsu);
  }
  int cur=dsu.history.size();
  while(cur>sz){
    dsu.rollback();
    cur--;
  }
}
void solve()
{
    int n,m,q; cin>>n>>m>>q;
    for(int i=0;i<m;i++){
      int u,v;
      cin>>u>>v;
      if(u>v)swap(u,v);
      last[{u,v}]=0;
    }
    for(int i=1;i<=q;i++){
      int t,u,v;
      cin>>t>>u>>v;
       if(u>v)swap(u,v);
      if(t==1){
        last[{u,v}]=i;
      }
      else{
        int l=last[{u,v}];
        pair<int,int>p={u,v};
        update(0,0,q,l,i-1,p);
        last.erase({u,v});
      }
    }
    for(auto p:last){
      pair<int,int>g=p.ff;
       update(0,0,q,p.ss,q,g);
    }
    RollbackDSU dsu(n);
    dfs(0,0,q,dsu);
    for(int i=0;i<=q;i++)cout<<ans[i]<<" ";
}
