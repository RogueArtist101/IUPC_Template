// Section: Data Structures
// Topic:   Wavelet Tree

class wavelet_tree{
    int lo, hi; // Range of values covered by this node
    wavelet_tree *l, *r; // Children
    vi b; // b[i] = how many of first i elements went to left child
    vll c; // c[i] = sum of first i elements
    wavelet_tree() : lo(1), hi(0), l(nullptr), r(nullptr) {}
    template<typename Iter>
    void build(Iter from, Iter to, int lo, int hi){
        this->lo = lo; this->hi = hi;
        if(from>=to) return;
        if(lo == hi){
            // Leaf node: all values equal lo == hi
            int len = to-from;
            b.resize(len+1); c.resize(len+1);
            b[0] = 0; c[0] = 0;
            f(i,0,len){
                b[i+1] = b[i] + 1;          
                c[i+1] = c[i] + *(from+i); 
            }
            return;
        }
        int mid = (lo + hi)/2;
        int len = to - from;
        b.resize(len + 1); c.resize(len + 1);
        b[0] = 0; c[0] = 0;
        f(i,0,len){
            b[i+1] = b[i] + (*(from+i)<=mid);
            c[i+1] = c[i] + *(from+i);
        }
        // Partition array for recursive build
        vector<int> left, right;
        left.reserve(b[len]);              // number of elements that go left
        right.reserve(len-b[len]);       // number of elements that go right
        for(auto it = from; it != to; it++){
            if((*it)<= mid) left.pb(*it);
            else right.pb(*it);
        }
        if(!left.empty()){
            l = new wavelet_tree();
            l->build(left.begin(), left.end(), lo, mid);
        }
        if(!right.empty()){
            r = new wavelet_tree();
            r->build(right.begin(), right.end(), mid+1, hi);
        }
    }
    public:
    // Constructor that builds tree directly from a vector (give 1 based)
    wavelet_tree(const vector<int> &v, int mn = -mod, int mx = mod){
        build(v.begin()+1, v.end(), mn, mx);
    }
    // kth smallest in [L, R]
    int kth(int L, int R, int k){
        if(L>R) return 0;
        if(lo==hi) return lo;
        int inLeft = b[R]-b[L-1]; // how many in [L,R] went left
        int lb = b[L-1], rb = b[R]; // prefix counts before and after
        if(k<=inLeft){
            return l->kth(lb+1, rb, k);
        }
        //Answer is in right child
        return r->kth(L-lb, R-rb, k-inLeft);
    }

    // Count numbers <= k in [L,R]
    int LTE(int L, int R, int k){
        if(L>R or k<lo) return 0;
        if(hi <= k) return R-L+1;
        int lb = b[L-1], rb = b[R];
        int left_count = 0, right_count = 0;
        if(l) left_count = LTE(lb+1, rb, k);
        if(r) right_count = LTE(L-lb, R-rb, k);
        return left_count+right_count;
    }

    // Count occurrences of number k in [L,R]
    int count(int L, int R, int k){
        if(L>R or k<lo or k>hi) return 0;
        if(lo==hi) return R-L+1;
        int lb = b[L-1], rb = b[R];
        int mid = (lo+hi)/2;
        if(k <= mid) return l ? l->count(lb+1, rb, k) : 0;
        return r ? r->count(L - lb, R - rb, k) : 0;
    }

    // Sum of numbers <= k in [L,R]
    ll sum(int L, int R, int k){
        if(L > R or k < lo) return 0;
        if(hi <= k) return c[R] - c[L-1];

        int lb = b[L-1], rb = b[R];
        ll left_sum = 0, right_sum = 0;
        if(l) left_sum = sum(lb+1, rb, k);
        if(r) right_sum = sum(L-lb, R-rb, k);
        return left_sum+right_sum;
    }
    ~wavelet_tree(){
        delete l;
        delete r;
    }
};
