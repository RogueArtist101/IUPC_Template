// Section: Math
// Topic:   Matrix Expo (Fib example)

struct Matrix {
    int n;
    vector<vector<ll>> a;
    Matrix(int n, bool ident = false): n(n), a(n, vector<ll>(n,0)) {
        if(ident) for(int i=0;i<n;i++) a[i][i]=1;
    }
    Matrix operator*(const Matrix &o) const {
        Matrix r(n);
        for(int i=0;i<n;i++){
            for(int k=0;k<n;k++) if(a[i][k]){
                ll x = a[i][k];
                for(int j=0;j<n;j++){
                    r.a[i][j] = (r.a[i][j] + x * o.a[k][j]) % MOD;
                }
            }
        }
        return r;
    }
};

Matrix mpow(Matrix base, long long exp) {
    Matrix res(base.n, true);
    while(exp){
        if(exp&1) res = res*base;
        base = base*base;
        exp >>= 1;
    }
    return res;
}

ll fib(long long n) {
    if(n==0) return 0;
    if(n==1) return 1;
    int d = 2;
    Matrix M(d);
    M.a = {
        {1,1},
        {1,0}
    }; 
    vector<ll> S = {1,0}; 
    Matrix P = mpow(M,n-1);
    vector<ll> res(d,0);
    for(int j=0;j<d;j++)
        for(int k=0;k<d;k++)
            res[j] = (res[j] + P.a[j][k]*S[k]) % MOD;
    return res[0];
}
