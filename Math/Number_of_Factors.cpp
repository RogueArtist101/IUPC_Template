// Section: Math
// Topic:   Number of Factors

int main() {
    fast
    /* 
    Theory: n = x*y where x has primes upto n^(1/3) and y has more
        first, find divisors from x.
        now to factorise y, notice y can be either a prime, square of a prime (or 1) or product of 2 primes
        check the first case using millar rabin, second case by sqrt func, else it's the third one
        gives a soln in O(n^(1/3) ) for the sieve and finding x,y
    */
    ll n;
    cin >> n;
    const int N = 1e6;
    vector<ll> primes; //write sieve
    ll ans =1;
    for(auto p: primes){
        if(p*p*p>n) break;
        ll cnt = 1;
        while(n%p==0){
            n/=p;
            cnt++;
        } 
        ans*=cnt;
    }

    if(MillerRabin(n)){
        cout << ans*2;
        return 0;
    }

    if(n!=1 and is_square(n)){
        cout << ans*3;
        return 0;
    }

    if(n!=1) ans *=4;
    cout << ans << endl;

}
