// Section: Math
// Topic:   CRT

ll extgcd(ll a, ll b, ll &x, ll &y){
    if(b==0){ x=1; y=0; return a; }
    ll x1,y1;
    ll g=extgcd(b,a%b,x1,y1);
    x=y1;
    y=x1 - (a/b)*y1;
    return g;
}

//combine two congruences: x ≡ r1 (mod m1), x ≡ r2 (mod m2)
pair<ll,ll> crt_merge(ll r1,ll m1,ll r2,ll m2){
    ll x,y;
    ll g=extgcd(m1,m2,x,y);
    if((r2-r1)%g!=0) return {0,-1}; // no solution
    ll lcm=(ll)m1/g*m2;
    ll k=(ll)(r2-r1)/g;
    ll tmp=(ll)x*k % (m2/g);
    if(tmp<0) tmp += (m2/g);
    ll res=(ll)r1 + (ll)m1*tmp;
    ll ans=(ll)((res%lcm + lcm)%lcm);
    return {ans,(ll)lcm};
}

// main CRT: v[i] mod a[i]
pair<ll,ll> crt(const vector<ll>& v,const vector<ll>& a){
    ll r=v[0], m=a[0];
    for(size_t i=1;i<v.size();i++){
        auto [nr,nm]=crt_merge(r,m,v[i],a[i]);
        if(nm==-1) return {0,-1}; // no solution
        r=nr; m=nm;
    }
    return {r,m}; // x ≡ r (mod m)
}
