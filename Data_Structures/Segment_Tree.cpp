// Section: Data Structures
// Topic:   Segment Tree

class segtree {
    int n;
    vector<long long> v, tree, lazy;
    // Build tree from input array
    void build(int at, int l, int r){ 
        if(l==r){ 
            tree[at] = v[l];
            return;
        }
        int mid = l+(r-l)/2;
        build(at*2, l, mid);
        build(at*2+1, mid+1, r);
        tree[at] = tree[at*2]+tree[at*2+1];
    }
    // Push down lazy value to children
    void push(int at, int l, int r){ 
        if(lazy[at]!=0){ 
            // Update current node
            tree[at] += 1LL*lazy[at]*(r - l+1);
            // Push down if not a leaf node
            if(l!=r){  
                lazy[at*2] += lazy[at];
                lazy[at*2+1] += lazy[at];
            }
            lazy[at] = 0;
        }
    }
    // Range update: add `val` to all elements in [L, R]
    void update(int at, int l, int r, int L, int R, long long val){ 
        push(at, l, r);
        if(r<L or l>R) return;           // No overlap
        if(L<=l && r<=R){                // Total overlap
            lazy[at] += val;
            push(at, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(at*2, l, mid, L, R, val);
        update(at*2+1, mid+1, r, L, R, val);
        tree[at] = tree[at*2]+ tree[at*2+1];
    }
    // Range query: get combined value from [L, R]
    long long query(int at, int l, int r, int L, int R){ 
        push(at, l, r);
        if(r<L or l>R) return 0;   // No overlap
        if(L<=l && r<=R) return tree[at]; // Total overlap
        int mid = (l + r) / 2;
        return query(at*2, l, mid, L, R) +
            query(at*2+1, mid+1, r, L, R);
    }

public:
    segtree(vector<long long> &arr){ 
        n = arr.size();
        v.resize(n + 1);
        tree.resize(4*n, 0);
        lazy.resize(4*n, 0);
        for (int i = 1; i <= n; i++) v[i] = arr[i - 1];
        build(1, 1, n);
    }
    void update(int L, int R, long long val){ 
        update(1, 1, n, L, R, val);
    }
    long long query(int L, int R){ 
        return query(1, 1, n, L, R);
    }
};
