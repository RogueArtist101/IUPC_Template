// Section: Data Structures
// Topic:   Bitset

struct MyBitset{
    int n;              // number of bits
    vector<uint64_t> b; // blocks
    MyBitset(int _n = 0) { init(_n); }
    void init(int _n){
        n = _n;
        b.assign((n + 63) / 64, 0);
    }
    void set(int pos){b[pos >> 6] |= (1ULL << (pos & 63));}
    void reset(int pos){
        int idx = pos >> 6;       // divide by 64 to find which block
        int bit = pos & 63;       // position inside that block
        b[idx] &= ~(1ULL << bit); // clear that bit
    }
    bool test(int pos) const{
        return (b[pos >> 6] >> (pos & 63)) & 1ULL;
    }
    void reset(){
        fill(b.begin(), b.end(), 0);
    }
    MyBitset operator~() const{
        MyBitset res(n);
        for (size_t i = 0; i < b.size(); i++)
            res.b[i] = ~b[i];
        // clear extra bits beyond n
        if (n % 64)
            res.b.back() &= (1ULL << (n % 64)) - 1;
        return res;
    }
    // in-place OR
    MyBitset &operator|=(const MyBitset &other){
        for (size_t i = 0; i < b.size(); i++) b[i] |= other.b[i];
        return *this;
    }
    // binary OR -> returns new MyBitset
    MyBitset operator|(const MyBitset &other) const{
        MyBitset res(n);
        for(size_t i = 0; i < b.size(); i++)
            res.b[i] = b[i] | other.b[i];
        return res;
    }
    // bitwise AND
    MyBitset &operator&=(const MyBitset &other){
        for (size_t i = 0; i < b.size(); i++) b[i] &= other.b[i];
        return *this;
    }
    MyBitset operator&(const MyBitset &other) const{
        MyBitset res(n);
        for (size_t i = 0; i < b.size(); i++)
            res.b[i] = b[i] & other.b[i];
        return res;
    }
    // XOR
    MyBitset &operator^=(const MyBitset &other){
        for (size_t i = 0; i < b.size(); i++) b[i] ^= other.b[i];
        return *this;
    }
    MyBitset operator^(const MyBitset &other) const{
        MyBitset res(n);
        for (size_t i = 0; i < b.size(); i++) res.b[i] = b[i] ^ other.b[i];
        return res;
    }
    // count set bits
    int count() const{
        int ans = 0;
        for (auto x : b) ans += __builtin_popcountll(x);
        return ans;
    }
};

int main(){
    int N = 50001;
    MyBitset bs1(N), bs2(N);
    // advantage->compile time N can be used
}
