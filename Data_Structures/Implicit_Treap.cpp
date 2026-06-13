// Section: Data Structures
// Topic:   Implicit Treap

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct Node {
    int val;        // value of the element
    int prior;      // priority
    int sz;         // size of subtree
    bool rev;       // lazy reverse flag
    int sum;        //sum of subtree
    int lazysum;      //lazy sum for range upd 
    Node *l, *r;
    Node(int v) {
        val = v;
        prior = rnd();
        sz = 1;
        rev = false;
        l = r = nullptr;
        sum=lazysum=0;
    }
};
struct ImplicitTreap {
    Node* root;
    ImplicitTreap() { root = nullptr; }
    // update size of subtree
    void upd(Node* t) {
        if (!t) return;
        t->sz = 1;
        t->sum=t->val;
        if (t->l) t->sz += t->l->sz,t->sum+=t->l->sum;;
        if (t->r) t->sz += t->r->sz,t->sum+=t->r->sum;
    }
    // push lazy flags
    void push(Node* t) {
        if (!t || !t->rev) return;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= true;
        if (t->r) t->r->rev ^= true;
        t->rev = false;
    }
    void pushlazy(Node*t){
        if(!t||t->lazysum==0)return;
        t->val+=t->lazysum;
        t->sum+=(t->sz)*(t->lazysum);
        if(t->l)t->l->lazysum+=t->lazysum;
        if(t->r)t->r->lazysum+=t->lazysum;
        t->lazysum=0;
    }
    // split treap into L (size=pos) and R (rest)
    void split(Node* t, int pos, Node* &l, Node* &r) {
        if (!t) { l = r = nullptr; return; }
        push(t);
        pushlazy(t);
        int curr = (t->l ? t->l->sz : 0) + 1;
        if (curr <= pos) {
            split(t->r, pos - curr, t->r, r);
            l = t;
        } else {
            split(t->l, pos, l, t->l);
            r = t;
        }
        upd(t);
    }
    // merge two treaps
    Node* merge(Node* l, Node* r) {
        push(l); push(r);pushlazy(l);pushlazy(r);
        if (!l || !r) return l ? l : r;
        if (l->prior > r->prior) {
            l->r = merge(l->r, r);
            upd(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            upd(r);
            return r;
        }
    }
    // insert value at position (0-indexed)
    void insert(int pos, int val) {
        Node *l, *r;
        split(root, pos , l, r);
        root = merge(merge(l, new Node(val)), r);
    }
    // erase element at position (0-indexed)
    void erase(int pos) {
        Node *l, *r, *mid;
        split(root, pos , l, r);
        split(r, 1, mid, r);
        delete mid;
        root = merge(l, r);
    }
    // reverse subarray [l, r] (0-indexed)
    void reverse(int l_pos, int r_pos) {
        Node *l, *mid, *r, *temp;
        split(root, l_pos , l, temp);
        split(temp, r_pos - l_pos + 1, mid, r);
        if (mid) mid->rev ^= true;
        root = merge(merge(l, mid), r);
    }
    //function for range update by value val
    void rangeupd(int l,int r,int val){
        Node *lft,*rt,*mid,*tem;
        split(root,l,lft,tem);
        split(tem,r-l+1,mid,rt);
        if(mid)mid->lazysum+=val;
        root=merge(merge(lft,mid),rt);
    }
    // inorder traversal to get array
    void inorder(Node* t, vector<int> &res) {
        if (!t) return;
        push(t);pushlazy(t);
        inorder(t->l, res);
        res.push_back(t->val);
        inorder(t->r, res);
    }
    vector<int> getArray() {
        vector<int> res;
        inorder(root, res);
        return res;
    }
    int subsum(int l,int r){
        Node *lft,*rt,*mid,*tem;
        split(root,l,lft,tem);
        split(tem,r-l+1,mid,rt);
        int ans=mid->sum;
        root=merge(merge(lft,mid),rt);
        return ans;
    }
};
int main() {
    ImplicitTreap treap;
    // create array [1,2,3,4,5]
    for (int i = 0; i < 5; i++) treap.insert(i, i+1);
    // insert 10 at position 2 -> [1,2,10,3,4,5]
    treap.insert(2, 10);
    // reverse subarray [1..3] -> [1,3,10,2,4,5]
    treap.reverse(1,3);
    // delete position 2 -> [1,3,2,4,5]
    treap.erase(2);
    vector<int> arr = treap.getArray(); //for printing
}
