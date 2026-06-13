// Section: Data Structures
// Topic:   HLD

const int N=100005, lg=18;
int a[N], n, t;
vector<int>adj[N];
int up[N][lg+1];
int sz[N],lvl[N],head[N],par[N],in[N];
void dfs(int u){
    sz[u]=1;
    for(auto &v:adj[u]){
      if(v==par[u])continue;
      par[v]=u;
      up[v][0]=u;
      for(int j=1;j<=lg;j++){
        up[v][j]=up[up[v][j-1]][j-1];
      }
      lvl[v]=lvl[u]+1;
      dfs(v);
      sz[u]+=sz[v];
      if(sz[v]>sz[adj[u][0]]||adj[u][0]==par[u]){
        swap(v,adj[u][0]);
      }
    }
}
void dfs_hld(int u){
   in[u]=t++;
   for(auto v:adj[u]){
    if(v==par[u])continue;
    if(v==adj[u][0])head[v]=head[u];
    else head[v]=v;
    dfs_hld(v);
   }
}
int findlca(int u,int v){
    if(lvl[u]>lvl[v])swap(u,v);
    int k=lvl[v]-lvl[u];
    for(int j=0;j<=lg;j++){
      if((k>>j)&1) v=up[v][j];
    }
   if(u==v) return u;
   for(int j=lg;j>=0;j--){
     if(up[u][j]!=up[v][j]){
      u=up[u][j];
      v=up[v][j];
     }
   }
   return up[u][0];
}
class Segment_tree{
private:
    int seg[4*N];
public:
void update(int node, int s, int e, int pos,int val)
{
   if (s == e)
   {
      seg[node] = val;
      return;
   }
   int m = (s + e) >> 1;
   if (pos <= m)
      update(2 * node + 1, s, m, pos, val);
   else
      update(2 * node + 2, m + 1, e, pos,val);
   seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
}
int point_query(int node, int s, int e, int l, int r)
{
   if (s > r || e < l)
      return 0;
   if (s >= l && e <= r)
      return seg[node];
   int m = (s + e) >> 1;
   return point_query(2 * node + 1, s, m, l, r) ^ point_query(2 * node + 2, m + 1, e, l, r);
}
};
int qry(int u,int v,Segment_tree &tr){
   int res=0;
   for(;head[u]!=head[v];v=par[head[v]]){
    if(lvl[head[u]]>lvl[head[v]])swap(u,v);
     int f=tr.point_query(0,0,n-1,in[head[v]],in[v]);
     res^=f;
   }
  if(lvl[u]>lvl[v])swap(u,v);
  int f=tr.point_query(0,0,n-1,in[u],in[v]);
     res^=f;
     return res;
}
void solve()
{
    int q;
   cin>>n>>q;
   for(int i=1;i<=n;i++)cin>>a[i];
   for(int i=1;i<n;i++){
    int u,v;
    cin>>u>>v;
    adj[u].pb(v);
    adj[v].pb(u);
   }
   par[1]=1;
   for(int i=0;i<=lg;i++)up[1][i]=1;
   dfs(1);
   head[1]=1;
   dfs_hld(1);  
   Segment_tree tr;
   for(int i=1;i<=n;i++){
    tr.update(0,0,n-1,in[i],a[i]);
   }
   while(q--){
    int t;
    cin>>t;
    if(t==1){
      int i,x;
      cin>>i>>x;
      a[i]=x;
      tr.update(0,0,n-1,in[i],x);
    }
    else{
      int u,v;
      cin>>u>>v;
      int l=findlca(u,v);
       int x=qry(l,u,tr);
      
       int y=qry(l,v,tr);
       cout<<(x^y^a[l])<<endl;
    }
   }
  // cout<<1<<endl;   
}
