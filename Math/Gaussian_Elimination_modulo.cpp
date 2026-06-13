// Section: Math
// Topic:   Gaussian Elimination modulo

int gauss(vector<vector<ll>> &a, vector<ll> &ans) {
    /*
    a = augmented matrix (n x (m+1))
    a11x1 + a12x2 = b1
    a21x1 + a22x2 = b2
    matrix:
    a11 a12 b1
    a21 a22 b2
    Solution assigned to ans
    */ 
    int n = a.size(), m = (int)a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        // Find pivot
        int sel = row;
        for (int i = row; i < n; i++) {
            if (a[i][col] != 0) { sel = i; break; }
        }
        if (a[sel][col] == 0) continue;

        swap(a[sel], a[row]);
        where[col] = row;

        // Normalize pivot row
        ll inverse = inv(a[row][col]);
        for (int j = col; j <= m; j++) {
            a[row][j] = a[row][j] * inverse % mod;
        }

        // Eliminate below
        for (int i = 0; i < n; i++) {
            if (i != row && a[i][col] != 0) {
                ll factor = a[i][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] = (a[i][j] - factor * a[row][j]) % mod;
                    if (a[i][j] < 0) a[i][j] += mod;
                }
            }
        }
        row++;
    }
    // Build answer
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) {
        if (where[i] != -1)
            ans[i] = a[where[i]][m];
    }
    // Check for inconsistency (0 = nonzero)
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int j = 0; j < m; j++) {
            sum = (sum + ans[j] * a[i][j]) % mod;
        }
        if (sum != a[i][m]) return 0; // no solution
    }
    // If infinite solutions print 1
    return 1; // at least one solution
}
