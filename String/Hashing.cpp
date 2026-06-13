// Section: String
// Topic:   Hashing

int power1[n+1],power2[n+1];
  int p1=31,p2=37,m1=127657753,m2=987654319;
  int hash1[n+1],hash2[n+1];
  hash1[0]=hash2[0]=0;
  power1[0]=power2[0]=1;
  for(int i=1;i<=n;i++){
     power1[i]=power1[i-1]*p1;
     power1[i]%=m1;
      power2[i]=power2[i-1]*p2;
     power2[i]%=m2;
  }
  for(int i=1;i<=n;i++){
   hash1[i]=(hash1[i-1]+(s[i-1]-'a'+1)*power1[i-1])%m1;
   hash2[i]=(hash2[i-1]+(s[i-1]-'a'+1)*power2[i-1])%m2;
  }
  vector<pair<int,int>>st;
   for(int l=1;l<=n;l++){
    for(int i=1;i+l-1<=n;i++){
      int r=0;
      for(int j=0;j<bad.size();j++){
         r+=cnt[bad[j]][i+l-1]-cnt[bad[j]][i-1];
      }
      if(r>k)continue;
      int h1=(hash1[i+l-1]-hash1[i-1]+m1)%m1;
      int h2=(hash2[i+l-1]-hash2[i-1]+m2)%m2;
      h1=(h1*power1[n-i])%m1;
      h2=(h2*power2[n-i])%m2;
      st.pb({h1,h2});
    }
   }
