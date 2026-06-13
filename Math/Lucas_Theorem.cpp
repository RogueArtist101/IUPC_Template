// Section: Math
// Topic:   Lucas Theorem

//find nCr mod p
ll nCr(ll n, ll r, ll p){
        const int N = p+1;
        ll fact[N];
        fact[0]=1;
        f(i,1,p) fact[i]=(fact[i-1]*i)%p;
        ll ans = 1;
        while(r>0){
            ll _n = n%p;
            n/=p;
            ll _r = r%p;
            r/=p;
            if(_r>_n){
                ans = 0;
                break;
            }
            ll x = (fact[_n-_r]* fact[_r])%p;
            ll y = inv(x,p);
            ll z = (fact[_n]*y)%p;
            ans = (ans*z)%p;
        }
        return ans;
}
