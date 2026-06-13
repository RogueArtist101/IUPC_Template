// Section: Dp optimization
// Topic:   Knuth Optimization

int cost(int i, int j){return calculated_cost;}
void knuth_dp(int n) {
    for (int i = 1; i <= n; i++) dp[i][i] = 0, opt[i][i] = i;
    for (int L = 2; L <= n; L++) {
        for (int i = 1, j = L; j <= n; i++, j++) {
            dp[i][j] = 1e18; // INF
            for (int k = opt[i][j - 1]; k <= min(j - 1, opt[i + 1][j]); k++) {
                long long val = dp[i][k] + dp[k + 1][j] + cost(i, j);
                if (val < dp[i][j]) dp[i][j] = val, opt[i][j] = k;}}}}
