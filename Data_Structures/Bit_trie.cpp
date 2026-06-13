// Section: Data Structures
// Topic:   Bit trie

struct Trienode{
  Trienode *children[2];
  int cntpref;
  Trienode()
  {
    cntpref=0;
    for (int i = 0; i < 2; i++)
      children[i] = NULL;
  }
};
class Trie{
    Trienode *root;
public:
  Trie(){ root=new Trienode(); }
  void insert(int x){
    Trienode *cur=root;
    for(int i=30;i>=0;i--){
        if((x>>i)&1){
            if(!cur->children[1]){
                cur->children[1]=new Trienode();
            }
             cur=cur->children[1];
             cur->cntpref++;
        }
        else{
            if(!cur->children[0]){
                cur->children[0]=new Trienode();
            }
             cur=cur->children[0];
             cur->cntpref++;
        }
    }
  }
  int max_xor(int y){
    Trienode *cur=root;
    int ans=0;
    for(int i=30;i>=0;i--){
        if((y>>i)&1){
            if(cur->children[0]!=NULL){
                ans+=((1LL)<<i);
                cur=cur->children[0];
            }
            else if(cur->children[1]!=NULL) cur=cur->children[1];
        }
        else{
             if(cur->children[1]!=NULL){
                ans+=((1LL)<<i);
                cur=cur->children[1];
            }
            else if(cur->children[0]!=NULL) cur=cur->children[0];
        }
    }
    return ans;
  }
  Trienode* eraseHelper(Trienode* node, int y, int bit) {
    if (!node) return NULL;
    if (bit < 0) node->cntpref--;
    else {
        int b = (y >> bit) & 1;
        node->children[b] = eraseHelper(node->children[b], y, bit - 1);
        node->cntpref--;  
    }
    if (node->cntpref == 0 && !node->children[0] && !node->children[1]) {
        delete node;
        return NULL;
    }
    return node;
}
  void erase(int y) root=eraseHelper(root,y,30);
};
