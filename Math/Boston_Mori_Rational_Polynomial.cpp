// Section: Math
// Topic:   Boston Mori (Rational Polynomial)

int bostan_mori(vector<int> P, vector<int> Q, long long k){
    while (k > 0) {
        vector<int> Q_neg = Q; 
        for (int i = 1; i < Q_neg.size(); i += 2) 
            Q_neg[i] = (MOD - Q_neg[i]) % MOD;
        P = multiply(P, Q_neg); //NTT
        Q = multiply(Q, Q_neg); 
        vector<int> P_new, Q_new;
        for (int i = (k & 1); i < P.size(); i += 2) P_new.push_back(P[i]);
        for (int i = 0; i < Q.size(); i += 2) Q_new.push_back(Q[i]);
        P = P_new;  Q = Q_new;
        k >>= 1;
    }
    return 1LL * P[0] * bigmod(Q[0], MOD - 2) % MOD;
}

// Finds k-th term of F[r] = c[1]F[r-1] + ... + c[n]F[r-n]
// F_init: {F[0], F[1], ... F[r-1]}
int solve(vector<int> c, vector<int> F_init, long long N) {
    if (N < F_init.size()) return F_init[N];
    // Q(x) = 1 - c[1]x - c[2]x^2 ...
    vector<int> Q = {1};
    for (int x : c) Q.push_back(x ? MOD - x : 0); 
    // P(x) = F(x)Q(x) mod x^k
    vector<int> P = multiply(F_init, Q); 
    if (P.size() > Q.size() - 1) P.resize(Q.size() - 1);
    return bostan_mori(P, Q, N);
}
