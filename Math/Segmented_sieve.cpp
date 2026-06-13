// Section: Math
// Topic:   Segmented sieve

vector<int> simple_sieve(int limit) {
    vector<char> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= limit; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (ll j = (ll)p * p; j <= limit; j += p)
                is_prime[j] = false;
        }
    }
    return primes;
}

// Segmented sieve on [L..R]
vector<ll> segmented_sieve(ll L, ll R) {
    ll range = R - L + 1;
    vector<char> is_prime(range, true);

    // Get small primes up to sqrt(R)
    int limit = floor(sqrt(R));
    vector<int> primes = simple_sieve(limit);

    // Mark multiples of each small prime in [L..R]
    for (int p : primes) {
        // first multiple >= L
        ll start = max((ll)p * p, ((L + p - 1) / p) * (ll)p);
        for (ll j = start; j <= R; j += p) {
            is_prime[j - L] = false;
        }
    }
    // 0 and 1 are not primes
    if (L == 0) {
        is_prime[0] = false;
        if (R >= 1) is_prime[1 - L] = false;
    }
    if (L == 1) {
        is_prime[0] = false;
    }

    // Collect survivors
    vector<ll> result;
    for (ll i = 0; i < range; i++) {
        if (is_prime[i]) result.push_back(L + i);
    }
    return result;
}

int main() {
    ll L, R;
    cin >> L >> R;
    // Example input: 100 120
    vector<ll> primes_in_range = segmented_sieve(L, R);
    // Output them
    for (ll p : primes_in_range) {
        cout << p << "\n";
    }
    return 0;
}
