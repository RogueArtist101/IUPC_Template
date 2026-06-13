// Section: Math
// Topic:   Barkalemp Massey (Linear Recurrence)

struct Mint {
    long long val;
    Mint(long long v = 0) : val((v % MOD + MOD) % MOD) {}
    Mint operator+(Mint o) const { return Mint(val + o.val); }
    Mint operator-(Mint o) const { return Mint(val - o.val); }
    Mint operator*(Mint o) const { return Mint(val * o.val); }
    Mint operator-() const { return Mint(-val); }
    bool operator==(Mint o) const { return val == o.val; }
    bool operator!=(Mint o) const { return val != o.val; }
    Mint inv() const {
        long long res = 1, b = val, e = MOD - 2;
        while (e > 0) {
            if (e % 2 == 1) res = (res * b) % MOD;
            b = (b * b) % MOD; e /= 2;
        }
        return Mint(res);
    }
    Mint operator/(Mint o) const { return *this * o.inv(); }
    void operator+=(Mint o) { *this = *this + o; }
    void operator-=(Mint o) { *this = *this - o; }
    void operator*=(Mint o) { *this = *this * o; }
};

// Polynomial multiplication modulo f(x)
vector<Mint> mul(const vector<Mint> &a, const vector<Mint> &b, const vector<Mint> &c) {
    int n = (int)c.size();
    vector<Mint> ret(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            ret[i + j] += a[i] * b[j];

    // Polynomial reduction: ret mod characteristic polynomial
    for (int i = (int)ret.size() - 1; i >= n; i--)
        for (int j = n - 1; j >= 0; j--)
            ret[i - j - 1] += ret[i] * c[j];
            
    ret.resize(min((int)ret.size(), n));
    return ret;
}

vector<Mint> berlekampMassey(const vector<Mint> &s) {
    vector<Mint> c, oldC; int f = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        Mint delta = s[i];
        for (int j = 1; j <= (int)c.size(); j++)
            delta -= c[j - 1] * s[i - j];
        if (delta == Mint(0)) continue;
        if (f == -1) { c.resize(i + 1); f = i; }
        else {
            vector<Mint> d = oldC;
            for (Mint &x : d) x = -x;
            d.insert(d.begin(), Mint(1));
            Mint df1 = 0;
            for (int j = 1; j <= (int)d.size(); j++)
                df1 += d[j - 1] * s[f + 1 - j];
            Mint coef = delta / df1;
            for (Mint &x : d) x *= coef;
            vector<Mint> zeros(i - f - 1);
            zeros.insert(zeros.end(), d.begin(), d.end());
            d = zeros;
            vector<Mint> temp = c;
            c.resize(max(c.size(), d.size()));
            for (int j = 0; j < (int)d.size(); j++) c[j] += d[j];
            if (i - (int)temp.size() > f - (int)oldC.size()) {
                oldC = temp; f = i;
            }
        }
    }
    return c;
}

Mint solve_recurrence(const vector<Mint> &s, const vector<Mint> &c, long long k) {
    int n = (int)c.size();
    if (k < (int)s.size()) return s[k];
    
    // a = x^1 mod f(x)
    vector<Mint> a = n == 1 ? vector<Mint>{c[0]} : vector<Mint>{0, 1};
    vector<Mint> x{1}; // Identity x^0
    
    for (; k > 0; k /= 2) {
        if (k % 2) x = mul(x, a, c);
        a = mul(a, a, c);
    }
    x.resize(n);
    Mint ret = 0;
    for (int i = 0; i < n; i++) ret += x[i] * s[i];
    return ret;
}

int main() {
    vector<Mint> s = {1, 5, 15, 41, 103, 249, 583, 1337, 3015, 6713};
    vector<Mint> c = berlekampMassey(s);
    ll n; cin >> n;
    cout << solve_recurrence(s, c, n - 1).val;
}
