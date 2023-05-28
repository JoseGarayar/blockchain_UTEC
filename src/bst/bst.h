#ifndef BSTREE_H
#define BSTREE_H
#include <queue>
#include <sstream>
#include "bstiterator.h"

using namespace std;

template<typename TK, typename TV>
class BSTree {
    public:
        typedef BSTIterator<TK, TV> iterator;  

    private:
        NodeBT<TK, TV>* root;    

    public:
        BSTree(): root(nullptr) {}

		void insert(TK key, TV value){
            _insert(key, value, root);
        }	
		bool find(TK key){
            return _find(root, key) != nullptr ? true : false;
        }

        string displayInOrder(){
            stringstream ss;
            _displayInOrder(root, ss);
            return ss.str();            
        }

        string displayPreOrder(){
            stringstream ss;
            _displayPreOrder(root, ss);
            return ss.str();            
        }

        string displayPostOrder(){
            stringstream ss;
            _displayPostOrder(root, ss);
            return ss.str();            
        }

        int height(){
            return _height(root);
        }

        TK minValue(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _findMin(root)->key; 
        }

        TK maxValue(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _findMax(root)->key; 
        }

        void remove(TK value){
            if (root == nullptr) throw out_of_range("BST is empty");
            _remove(root, value);
        }       
        
        bool isBalanced(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _isBalanced(root);
        }

        int size(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _size(root);
        }

        bool isFull(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _isfull(root);
        } //es aquel en el que todos los nodos tienen 0 o 2 hijos  

        TK successor(TK value){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _successor(root, nullptr, value)->key;
        } // Retornar el valor siguiente de "value" en el arbol

        TK predecessor(TK value){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _predecessor(root, nullptr, value)->key;
        } // Retornar el valor anterior de "value" en el arbol


        void clear(){
            if (root!=nullptr)
                _KillSelf(root);
        } // Liberar todos los nodos (usar root->KillSelf)

        void buildFromOrderedArray(TK *array, int n){
                root = _buildFromOrderedArray(array,0,n-1);
        }//dado un array ordenado construir un arbol binario balanceado


        vector<pair<TK, TV>> findRange(TK valueStart, TK valueEnd){// Recorrido en anchura (BreadthFirstSearch)

            vector<pair<TK, TV>> result;
            if (root == nullptr) {
                return result;
            }
            _findRange(root, valueStart, valueEnd, result);
            
            return result;
        }

        vector<pair<TK, TV>> findKey(TK key){
            vector<pair<TK, TV>> result;

            _findKey(root, key, result) ;
            return result;
        }
        
        string displayBFS(){// Recorrido en anchura (BreadthFirstSearch)

            if (root == nullptr) {
                return "";
            }

            stringstream ss;
            queue<NodeBT<TK, TV>*> q;
            q.push(root);

            while (!q.empty()) {
                NodeBT<TK, TV>* current = q.front();
                ss << current->key << " ";
                q.pop();

                if (current->left != nullptr) {
                    q.push(current->left);
                }

                if (current->right != nullptr) {
                    q.push(current->right);
                }
            }
            return ss.str();
        }

        string displayDFS(){// Recorrido en profundidad (DepthFirstSearch)
            stringstream ss;
            _displayDFS(root, ss);
            return ss.str();
        }



        iterator begin(TypeBSTOrder tipo = TypeBSTOrder::InOrder){// Retorna el inicio del iterador             
            return  iterator(root, tipo); //new iterator(root, type);
        }

        iterator end(){
            return nullptr;
        }// Retorna el final del iterador

        ~BSTree(){
            if (root!=nullptr)
                _KillSelf(root);
                //root->KillSelf();
        } //Destructor del arbol
    
    private:

        void _KillSelf(NodeBT<TK,TV>* &node){
            if (node !=nullptr){
                _KillSelf(node->left);
                _KillSelf(node->right);
                NodeBT<TK, TV>* nodetmp = node; //nodo a eliminar                
                node=nullptr;
                nodetmp->left =nullptr;
                nodetmp->right =nullptr;
                delete nodetmp;
            }
        } 

        void _insert(TK key, TV value,NodeBT<TK,TV>* &node){
            if (node==nullptr) node = new NodeBT<TK,TV>(key,value);                                
            else if (key < node->key) _insert(key, value, node->left);
            else _insert(key,value, node->right);
        }

        void _displayInOrder(NodeBT<TK,TV>* node, stringstream & ss){

            if (node != nullptr) {
                _displayInOrder(node->left, ss);
                ss << node->key << " ";
                _displayInOrder(node->right, ss);
            }

        }

        void _displayPreOrder(NodeBT<TK,TV>* node, stringstream & ss){

            if (node != nullptr) {
                ss << node->key << " ";
                _displayInOrder(node->left, ss);                
                _displayInOrder(node->right, ss);
            }
        }


        void _displayPostOrder(NodeBT<TK,TV>* node, stringstream & ss){

            if (node != nullptr) {
                
                _displayInOrder(node->left, ss);                
                _displayInOrder(node->right, ss);
                ss << node->key << " ";
            }
        }

        NodeBT<TK,TV>* _findMin(NodeBT<TK,TV>* node) {
            while (node->left!=nullptr){
                node = node->left;
            }                
            return node;                        
        }

        NodeBT<TK,TV>* _findMax(NodeBT<TK,TV>* node) {
            while (node->right!=nullptr){
                node = node->right;
            }                
            return node;                        
        }

        NodeBT<TK,TV>* _find(NodeBT<TK, TV>* node, TK key){
            if (node== nullptr || key == node->key) return node;
            if (key < node->key) return _find(node->left, key);
            else return _find(node->right, key);            
        }

        int _height(NodeBT<TK, TV>* node)
        {
            if (node == nullptr || (node->left==nullptr && node->right==nullptr)) return 0;            
            return 1+ max(_height(node->left), _height(node->right));
        }

        bool _isBalanced(NodeBT<TK, TV>* node){
            
            if (node == nullptr) return true;

            int heightLeft = _height(node->left);
            int heightright = _height(node->right);

            if (abs(heightLeft-heightright)<=1 && _isBalanced(node->left) && _isBalanced(node->right))
                return true;
            return false;
        
        }

        void _remove(NodeBT<TK, TV>* &node,TK key){

            if ( node == nullptr) return;

            if ( key < node->key ) _remove(node->left, key);
            else if ( key > node->key ) _remove(node->right, key);
            else if (node->left !=nullptr && node->right!=nullptr){
                node->key = _findMin(node->right)->key;
                _remove (node->right, node->key);
            }
            else{
                NodeBT<TK, TV>* nodetmp = node; //nodo a eliminar
                node = node->left!=nullptr ? node->left : node->right;
                delete nodetmp;
            }
        }

        bool _isfull(NodeBT<TK,TV>* node){
            
            if (node==nullptr) return true;
            if (node->left == nullptr && node->right == nullptr){
                return true;
            }
            if (node->left != nullptr && node->right != nullptr){
                return (_isfull(node->left) && _isfull(node->right));
            }
            return false;

        }

        int _size(NodeBT<TK,TV>* node){
            if (node == nullptr)
                return 0;
            else
                return (_size(node->left)+1+_size(node->right));
        }

        NodeBT<TK,TV>* _successor(NodeBT<TK,TV>* node, NodeBT<TK,TV>* succ,TK key){

            if (node == nullptr) return succ;
            if (node->key == key){
                if (node->right!=nullptr) return _findMin(node->right);
            }
            else if (node->key < key){ //si esta value y su sucesor a la derecha
                return _successor(node->right, succ, key);
            }
            else { //si esta value y su sucesor a la izquierda voy guardando el padre en succesor
                succ = node;
                return _successor(node->left, succ, key);
            }
            return succ;

        }

        NodeBT<TK,TV>* _predecessor(NodeBT<TK,TV>* node, NodeBT<TK,TV>* prede,TK key){

            if (node == nullptr) return prede;
            if (node->key == key){
                if (node->left!=nullptr) return _findMax(node->left);
            }
            else if (node->key < key){ //si esta value y su predecessor a la derecha voy guardando el padre en predecessor
                prede = node;
                return _predecessor(node->right, prede, key);
            }
            else { //si esta value y su predecessor a la izquierda                 
                return _predecessor(node->left, prede, key);
            }
            return prede;

        }

        NodeBT<TK,TV>* _buildFromOrderedArray(TK arr[], int start, int end) {
            if (start > end) {
                return nullptr;
            }

            int mid = (start + end) / 2;
            
            NodeBT<TK,TV> *node = new NodeBT<TK,TV>(arr[mid]);

            node->left = _buildFromOrderedArray(arr, start, mid - 1);
            node->right = _buildFromOrderedArray(arr, mid + 1, end);

            return node;
        }

        void _displayDFS(NodeBT<TK,TV>* nodo, stringstream& ss) {
            if (nodo != nullptr) {
                ss << nodo->key << " ";
                _displayDFS(nodo->left, ss);
                _displayDFS(nodo->right, ss);
            }
        }

        void _findRange(NodeBT<TK, TV>* node,TK valueStart, TK valueEnd, vector<pair<TK, TV>> &result){
            if (node ==nullptr) return;

            if (valueStart < node->key  ) {
                _findRange (node->left, valueStart, valueEnd,result);
            }
            ///argrega valor
            if (valueStart <= node->key && valueEnd >= node->key){
                result.push_back(make_pair(node->key,node->value));
            }
            if (valueEnd > node->key ) {
             _findRange (node->right, valueStart, valueEnd,result);
            }
        }

        void _findKey(NodeBT<TK, TV>* node,TK value, vector<pair<TK, TV>> &result){
            if (node ==nullptr) return;

            if (value < node->key  ) {
                _findKey (node->left, value,result);
            }
            ///argrega valor
            if (value == node->key ){
                result.push_back(make_pair(node->key,node->value));
            }
            if (value >= node->key ) {
             _findKey (node->right, value,result);
            }
        }


}; 


#endif


