// Section: Math
// Topic:   NTT

const int G = 3;

void NTT(vector<int> &a, bool invert = false) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = bigmod(G, (mod - 1) / len);
        if (invert) wlen = inv(wlen);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j];
                int v = (int)(w * a[i + j + len / 2] % mod);
                a[i + j] = (u + v < mod ? u + v : u + v - mod);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + mod);
                w = w * wlen % mod;
            }
        }
    }
    if (invert) {
        int inv_n = inv(n);
        for (int &x : a) x = 1LL * x * inv_n % mod;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    if (a.empty() || b.empty()) return {};
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    NTT(fa, false); NTT(fb, false);
    for (int i = 0; i < n; i++) fa[i] = 1LL * fa[i] * fb[i] % mod;
    NTT(fa, true);
    vector<int> res = fa;
    while (!res.empty() && res.back() == 0) res.pop_back();
    return res;
}

vector<int> poly_inv(const vector<int> &A, int deg) {
    if (deg == 0) return {};
    vector<int> R(1, inv(A[0])); 
    int m = 1;
    while (m < deg) {
        m <<= 1;
        vector<int> A_cut(min((int)A.size(), m));
        for (int i = 0; i < A_cut.size(); i++) A_cut[i] = A[i];
        vector<int> R2 = R;
        A_cut.resize(2 * m); R2.resize(2 * m);
        NTT(A_cut, false); NTT(R2, false);
        for (int i = 0; i < 2 * m; i++) {
            R2[i] = 1LL * R2[i] * (2 - 1LL * A_cut[i] * R2[i] % mod + mod) % mod;
        }
        NTT(R2, true);
        R2.resize(m); R = R2;
    }
    R.resize(deg);
    return R;
}

pair<vector<int>, vector<int>> poly_div(vector<int> A, vector<int> B) {
    int n = A.size(), m = B.size();
    if (n < m) return {{0}, A};
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    vector<int> Binv = poly_inv(B, n - m + 1);
    vector<int> Q = multiply(A, Binv);
    Q.resize(n - m + 1);
    reverse(Q.begin(), Q.end());
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    vector<int> BQ = multiply(B, Q);
    vector<int> R(n);
    for (int i = 0; i < n; i++) {
        R[i] = (A[i] - (i < BQ.size() ? BQ[i] : 0) + mod) % mod;
    }
    while (!R.empty() && R.back() == 0) R.pop_back();
    return {Q, R};
}

// Polynomial Derivative: P'(x)
vector<int> poly_deriv(const vector<int> &A) {
    if (A.size() <= 1) return {0};
    vector<int> res(A.size() - 1);
    for (int i = 1; i < A.size(); i++) {
        res[i - 1] = 1LL * A[i] * i % mod;
    }
    return res;
}

// Polynomial Integral: int P(x) dx
vector<int> poly_integral(const vector<int> &A) {
    if (A.empty()) return {0};
    vector<int> res(A.size() + 1, 0);
    for (int i = 0; i < A.size(); i++) {
        res[i + 1] = 1LL * A[i] * inv(i + 1) % mod;
    }
    return res;
}

// Polynomial Logarithm: ln(A(x)). Requires A[0] == 1.
vector<int> poly_ln(const vector<int> &A, int deg) {
    assert(!A.empty() && A[0] == 1);
    vector<int> deriv = poly_deriv(A);
    vector<int> inv = poly_inv(A, deg);
    vector<int> res = poly_integral(multiply(deriv, inv));
    res.resize(deg);
    return res;
}

// Polynomial Exponential: exp(A(x)). Requires A[0] == 0.
vector<int> poly_exp(const vector<int> &A, int deg) {
    assert(A.empty() || A[0] == 0);
    vector<int> E = {1};
    int m = 1;
    while (m < deg) {
        m <<= 1;
        vector<int> ln_E = poly_ln(E, m);
        vector<int> diff(m, 0);
        diff[0] = 1; 
        for (int i = 0; i < m; i++) {
            int a_val = (i < A.size() ? A[i] : 0);
            diff[i] = (diff[i] - ln_E[i] + a_val + mod) % mod;
            if (diff[i] >= mod) diff[i] -= mod;
        }
        E = multiply(E, diff);
        E.resize(m);
    }
    E.resize(deg);
    return E;
}

// Polynomial Power using Binary Exponentiation
// Computes A(x)^k modulo x^deg in O(deg * log(deg) * log(k))
// deg = max index you care about + 1
vector<int> poly_pow(vector<int> A, long long k, int deg) {
    vector<int> res = {1}; // Identity polynomial
    A.resize(min((int)A.size(), deg));

    while (k > 0) {
        if (k % 2 == 1) {
            res = multiply(res, A);
            if (res.size() > deg) res.resize(deg);
        }
        A = multiply(A, A);
        if (A.size() > deg) A.resize(deg);
        k /= 2;
    }
    return res;
}

//for unlabeled counting
// Unified Euler Transform (Multiset / Knapsack)
// D: Array of valid item counts of weight i.
// W: Array of allowed multiplicities (e.g. {0,1} for distinct, {0,1,2...} for all)
vector<int> euler_transform(const vector<int>& D, const vector<int>& W, int deg) {
    vector<int> w(deg, 0);
    for (int k : W) if (k < deg) w[k] = 1;
    
    vector<int> L = poly_ln(w, deg);
    vector<int> A(deg, 0);
    
    for (int i = 1; i < deg; i++) {
        if (D[i] == 0) continue;
        for (int j = 1; i * j < deg; j++) {
            long long term = 1LL * D[i] * L[j] % MOD;
            A[i * j] = (A[i * j] + term) % MOD;
        }
    }
    return poly_exp(A, deg);
}
