// Section: Graph Algorithms
// Topic:   Dominator tree

const int N=200002;
vector<int> g[N];
vector<int> tr[N],rg[N],bucket[N];
int sdom[N],par[N],dom[N],dsu[N],label[N];
int arr[N],rev[N],T;
int SZ(vector<int>&v){
    return v.size();
}
int Find(int u,int x=0){
	if(u==dsu[u])return x?-1:u;
	int v = Find(dsu[u],x+1);
	if(v<0)return u;
	if(sdom[label[dsu[u]]] < sdom[label[u]])
		label[u] = label[dsu[u]];
	dsu[u] = v;
	return x?v:label[u];
}
void Union(int u,int v) //Add an edge u-->v{
	dsu[v]=u; 	//yup,its correct :)
}
void dfs0(int u){
	T++;arr[u]=T;rev[T]=u;
	label[T]=T;sdom[T]=T;dsu[T]=T;
	for(int i=0;i<g[u].size();i++){
		int w = g[u][i];
		if(!arr[w])dfs0(w),par[arr[w]]=arr[u];
		rg[arr[w]].pb(arr[u]);
	}
}
void build_domtree(int s){
    dfs0(s);
    int n=T;
    for(int i=n;i>=1;i--){
		for(int j=0;j<SZ(rg[i]);j++)
			sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
		if(i>1)bucket[sdom[i]].pb(i);
		for(int j=0;j<SZ(bucket[i]);j++){
			int w = bucket[i][j];
			int v = Find(w);
			if(sdom[v]==sdom[w])dom[w]=sdom[w];
			else dom[w] = v;
		}
		if(i>1)Union(par[i],i);
	}
	for(int i=2;i<=n;i++){
		if(dom[i]!=sdom[i])
			dom[i]=dom[dom[i]];
		tr[rev[i]].pb(rev[dom[i]]);
		tr[rev[dom[i]]].pb(rev[i]);
	}
}
int main(){
    int src;
    build_domtree(src);
    //Then use normal dfs or something on tr to find ans
	//subtreesize[u]=no of vertices that u dominates.or u is present in all path from source to those vertices.
}
