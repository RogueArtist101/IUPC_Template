// Section: Graph Algorithms
// Topic:   Articulation point

const int N=1e5+2;
vector<int>adj[N];
int n,m, tme;
int low[N],disc[N]; 
bool ap[N];
void dfs(int u,int p){
    low[u]=disc[u]=++tme;
    int chld=0;
    for(auto x:adj[u]){
        if(x==p)continue;
        if(!disc[x]){
            chld++;
            dfs(x,u);
            if(disc[u]<=low[x]&&p!=-1)ap[u]=1;
            low[u]=min(low[u],low[x]);
        }
        else low[u]=min(low[u],disc[x]);
    }
    if(p==-1&&chld>1)ap[u]=1;
}
void solve(){
    //build adj, n nodes m edges
    tme=0;
    for(int i=1;i<=n;i++){
        if(disc[i])continue;
        dfs(i,-1);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(ap[i])ans++;
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)if(ap[i])cout<<i<<" ";
    cout<<endl;
}
