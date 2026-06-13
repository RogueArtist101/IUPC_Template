// Section: String
// Topic:   Suffix Array

vector<int> suffix_array(string s) {
    s += "$";
    int n = s.size();
    vector<int> sa(n), c(n);
    vector<pair<char,int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) sa[i] = a[i].second;
    c[sa[0]] = 0;
    for (int i = 1; i < n; i++)
        c[sa[i]] = c[sa[i-1]] + (a[i].first != a[i-1].first);
    int k = 0;
    while ((1 << k) < n) {
        vector<pair<pair<int,int>,int>> b(n);
        for (int i = 0; i < n; i++)
            b[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        sort(b.begin(), b.end());
        for (int i = 0; i < n; i++)
            sa[i] = b[i].second;
        vector<int> c_new(n);
        c_new[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            c_new[sa[i]] = c_new[sa[i-1]] +
                           (b[i].first != b[i-1].first);

        c = c_new;
        k++;
    }
    return sa;
}
vector<int> lcp_array(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n, 0), lcp(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == 0) {
            k = 0; continue;
        }
        int j = sa[rank[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}
