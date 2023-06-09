#ifndef NODE_H
#define NODE_H

using namespace std;

template<typename TK, typename TV>
struct NodeBT {
    
    TK key;
    TV value;
    NodeBT* left; 
    NodeBT* right;  
    
    NodeBT() : left(nullptr), right(nullptr) {}   
    NodeBT(TK key, TV value) : key(key), value(value), left(nullptr), right(nullptr) {}   
    NodeBT(TK key) : key(key), left(nullptr), right(nullptr) {}   

    void KillSelf(){
        // TODO
        _KillSelf(this);
    }

private:
    void _KillSelf(NodeBT<TK, TV>* node){
        if (node !=nullptr){
            _KillSelf(node->left);
            _KillSelf(node->right);
            node->left=nullptr;
            node->right=nullptr;
            delete node;
        }
    } 

};

#endif