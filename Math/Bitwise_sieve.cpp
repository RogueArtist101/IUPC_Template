// Section: Math
// Topic:   Bitwise sieve

const int N=1e8;
int sv[(N/32)+2];
vector<int>pr;
bool check(int n,int pos){
  return (n>>pos)&1;
}
void setbit(int &n,int pos){
  n|=(1<<pos);
}
void solve()
{
  long long n;
  cin>>n;
  long long k=n;
  long long ans=1;
  for(auto x:pr){
    if(1LL*x*x>n)break;
    long long ct=(long long)x;
    while(n%x==0){
      n/=x;
      ct*=x;
    }
    ct--;
    ct/=(1LL*(x-1));
    ans*=ct;
  }
  //cout<<ans<<endl;
  if(n>1){
    ans*=(n+1);
  }
  cout<<ans-k<<endl;
  
}
signed main()
{
  noob int t = 1, cs = 1;
  for(int i=3;i*i<=N;i+=2){
    if(check(sv[i>>5],i&31))continue;
    for(int j=i*i;j<=N;j+=i){
      setbit(sv[j>>5],j&31);
    }
  }
  pr.pb(2);
  for(int i=3;i<=N;i+=2){
    if(!check(sv[i>>5],i&31))pr.pb(i);
  }
  cin >> t;
  while (t--)
  {
    //  cout<<"Case "<<cs++<<": ";
    solve();
  }

  return 0;
}
