// Section: Math
// Topic:   Baby Step Giant Step

// Smallest x such that a^x = b (mod m) 
ll discrete_log(ll a, ll b, ll m) {
    a %= m; b %= m;
    long long val = 1;
    for (int i = 0; i <= 100; ++i) {
        if (val == b) return i;
        val = (__int128)val * a % m;
    }
    long long k = 1, add = 0, g;
    while ((g = gcd(a, m)) > 1) {
        if (b % g != 0) return -1; // Solution impossible
        b /= g; m /= g;
        add++;
        k = (__int128)k * (a / g) % m;
    }
    long long n = sqrt(m) + 1;
    gp_hash_table<long long, int, custom_hash> table;
    long long cur = b;
    for (int j = 0; j <= n; ++j) {
        table[cur] = j; cur = (__int128)cur * a % m;
    }
    long long giant_step = 1;
    for (int i = 0; i < n; ++i) giant_step = (__int128)giant_step * a % m;
    long long giant_val = k;
    for (int i = 1; i <= n; ++i) {
        giant_val = (__int128)giant_val * giant_step % m;
        if (table.find(giant_val) != table.end()) {
            long long j = table[giant_val];
            long long x = n * i - j;
            return add + x;
        }
    }
    return -1;
}
