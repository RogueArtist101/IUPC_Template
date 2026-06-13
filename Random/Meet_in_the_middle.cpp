// Section: Random
// Topic:   Meet in the middle

void meet(vector<int>&v,map<int,set<int>>&m){
  int n=v.size();
  for(int i=0;i<(1<<n);i++){
    for(int j=i;;j=(j-1)&i){
        int sum=0;
        for(int k=0;k<n;k++){
            if((j>>k)&1)sum+=v[k];
            else if((i>>k)&1)sum-=v[k];
        }
    m[sum].insert(i);
    if(j==0)break;
    }
  }
}
void solve(){
     int n; cin>>n;
     int a[n];
     vector<int>v,p;
     for(int i=0;i<n;i++){
      cin>>a[i];
      if(i<n/2)v.pb(a[i]);
      else p.pb(a[i]);
     }
     map<int,set<int>>m1,m2;
     meet(v,m1);
     meet(p,m2);
     int l=v.size();
     vector<int>ans(1<<n,0);
     for(auto x:m1){
      if(m2[x.ff].empty())continue;
      for(auto y:m1[x.ff]){
        for(auto z:m2[x.ff]){ 
          ans[y|(z<<l)]=1;
        }
      }
     }
    int res=0;
    for(int i=1;i<(1<<n);i++){
      if(ans[i])res++;
    }
    cout<<res<<endl;
}
