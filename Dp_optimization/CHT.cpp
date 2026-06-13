// Section: Dp optimization
// Topic:   CHT

// Slopes (m) are added in STRICTLY INCREASING order and
// Queries (x) are made in STRICTLY INCREASING order.
// Otherwise use dynamic which is O(log n), this is O(1)


//Both structures written for maximum query,for minimum cht.add(-m,-c) should be called and ans=-query(x)

struct CHT {
    struct Line { ll m, c; ll eval(ll x) { return m * x + c; } };
    deque<Line> dq;
    
    bool bad(Line l1, Line l2, Line l3) {
        return (long double)(l1.c - l2.c) / (l2.m - l1.m) >= (long double)(l2.c - l3.c) / (l3.m - l2.m);
    }
    void add(ll m, ll c) {
        Line l3 = {m, c};
        while (dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), l3)) dq.pop_back(); dq.push_back(l3);
    }
    ll query(ll x) {
        while (dq.size() >= 2 && dq[0].eval(x) <= dq[1].eval(x)) dq.pop_front(); return dq.front().eval(x);
    }
};
