// Section: Data Structures
// Topic:   Fenwick Tree

struct fenwick_tree{
    int n;
    vector<int> bit;
    fenwick_tree(int n){
        this->n = n;
        bit.resize(n + 1);
    }
    void update(int i, int x){
        for(;i<=n;i+=(i & -i)) bit[i]+=x;
    }
    int query(int i){
        int sum = 0;
        for(;i>0;i-=(i&-i)) sum+=bit[i];
        return sum;
    }
};
void update(int i,int j,int n,int m,vector<vector<int>>&bit,int val){
    while(i<=n){
        int y=j;
        while(y<=m){
            bit[i][y]+=val;
            y+=y&-y;
        }
        i+=i&-i;
    }
}
int res(int i,int j,vector<vector<int>>&bit){
    int ct=0;
    while(i>0){
        int y=j;
        while(y>0){
            ct+=bit[i][y];
            y-=y&-y;
        }
        i-=i&-i;
    }
    return ct;
}
