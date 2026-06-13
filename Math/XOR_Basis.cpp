// Section: Math
// Topic:   XOR Basis

const int LOG_K = 62; 

struct LinearBasis {
    vector<ll> basis;
    int sz;
    LinearBasis() {
        basis.assign(LOG_K, 0);
        sz=0;
    }
    bool insert(ll mask){
        ll temp = mask;
        for(int i = 61;i>=0;i--){
            if((temp>>i) & 1){
                if(!basis[i]){
                    basis[i] = temp;
                    sz++;
                    for(int j = 0;j<i;j++){
                        if(basis[j] and ((basis[i]>>j) & 1)){
                            basis[i]^= basis[j];
                        }
                    }
                    for(int j = 61;j>i;j--){
                        if(basis[j] and ((basis[j]>>i) & 1)){
                            basis[j]^= basis[i];
                        }
                    }
                    return true; 
                }
                temp^= basis[i];
            }
        }
        return false;
    }
    ll max_xor() {
        ll res = 0;
        for (int i = LOG_K - 1; i >= 0; i--) {
            if ((res ^ basis[i]) > res) {
                res ^= basis[i];
            }
        }
        return res;
    }
};
