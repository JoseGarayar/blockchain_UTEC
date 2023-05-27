#ifndef NODE_H
#define NODE_H

using namespace std;

template <typename T>
struct NodeBT {
    
    T data;
    NodeBT* left; 
    NodeBT* right;  
    
    NodeBT() : left(nullptr), right(nullptr) {}   
    NodeBT(T value) : data(value), left(nullptr), right(nullptr) {}   
    void KillSelf(){
        // TODO
        _KillSelf(this);
    }

private:
    void _KillSelf(NodeBT<T>* node){
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