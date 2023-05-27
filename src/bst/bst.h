#ifndef BSTREE_H
#define BSTREE_H
#include <queue>
#include <sstream>
#include "bstiterator.h"

using namespace std;

template <typename T>
class BSTree {
    public:
        typedef BSTIterator<T> iterator;  

    private:
        NodeBT<T>* root;    

    public:
        BSTree(): root(nullptr) {}

		void insert(T value){
            _insert(value, root);
        }	
		bool find(T value){
            return _find(root, value) != nullptr ? true : false;
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

        T minValue(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _findMin(root)->data; 
        }

        T maxValue(){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _findMax(root)->data; 
        }

        void remove(T value){
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

        T successor(T value){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _successor(root, nullptr, value)->data;
        } // Retornar el valor siguiente de "value" en el arbol

        T predecessor(T value){
            if (root == nullptr) throw out_of_range("BST is empty");
            return _predecessor(root, nullptr, value)->data;
        } // Retornar el valor anterior de "value" en el arbol


        void clear(){
            if (root!=nullptr)
                _KillSelf(root);
        } // Liberar todos los nodos (usar root->KillSelf)

        void buildFromOrderedArray(T *array, int n){
                root = _buildFromOrderedArray(array,0,n-1);
        }//dado un array ordenado construir un arbol binario balanceado

               vector<T> findRange(T valueStart, T valueEnd){// Recorrido en anchura (BreadthFirstSearch)

            vector<T> result;
            if (root == nullptr) {
                return result;
            }
            _findRange(root, valueStart, valueEnd, result);
            
            return result;
        }



        string displayBFS(){// Recorrido en anchura (BreadthFirstSearch)

            if (root == nullptr) {
                return "";
            }

            stringstream ss;
            queue<NodeBT<T>*> q;
            q.push(root);

            while (!q.empty()) {
                NodeBT<T>* current = q.front();
                ss << current->data << " ";
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

        void _KillSelf(NodeBT<T>* &node){
            if (node !=nullptr){
                _KillSelf(node->left);
                _KillSelf(node->right);
                NodeBT<T>* nodetmp = node; //nodo a eliminar                
                node=nullptr;
                nodetmp->left =nullptr;
                nodetmp->right =nullptr;
                delete nodetmp;
            }
        } 

        void _insert(T value,NodeBT<T>* &node){
            if (node==nullptr) node = new NodeBT<T>(value);                                
            else if (value < node->data) _insert(value, node->left);
            else _insert(value, node->right);
        }

        void _displayInOrder(NodeBT<T>* node, stringstream & ss){

            if (node != nullptr) {
                _displayInOrder(node->left, ss);
                ss << node->data << " ";
                _displayInOrder(node->right, ss);
            }

        }

        void _displayPreOrder(NodeBT<T>* node, stringstream & ss){

            if (node != nullptr) {
                ss << node->data << " ";
                _displayInOrder(node->left, ss);                
                _displayInOrder(node->right, ss);
            }
        }


        void _displayPostOrder(NodeBT<T>* node, stringstream & ss){

            if (node != nullptr) {
                
                _displayInOrder(node->left, ss);                
                _displayInOrder(node->right, ss);
                ss << node->data << " ";
            }
        }

        NodeBT<T>* _findMin(NodeBT<T>* node) {
            while (node->left!=nullptr){
                node = node->left;
            }                
            return node;                        
        }

        NodeBT<T>* _findMax(NodeBT<T>* node) {
            while (node->right!=nullptr){
                node = node->right;
            }                
            return node;                        
        }

        NodeBT<T>* _find(NodeBT<T>* node, T value){
            if (node== nullptr || value == node->data) return node;
            if (value < node->data) return _find(node->left, value);
            else return _find(node->right, value);            
        }

        int _height(NodeBT<T>* node)
        {
            if (node == nullptr || (node->left==nullptr && node->right==nullptr)) return 0;            
            return 1+ max(_height(node->left), _height(node->right));
        }

        bool _isBalanced(NodeBT<T>* node){
            
            if (node == nullptr) return true;

            int heightLeft = _height(node->left);
            int heightright = _height(node->right);

            if (abs(heightLeft-heightright)<=1 && _isBalanced(node->left) && _isBalanced(node->right))
                return true;
            return false;
        
        }

        void _remove(NodeBT<T>* &node,T value){

            if ( node == nullptr) return;

            if ( value < node->data ) _remove(node->left, value);
            else if ( value > node->data ) _remove(node->right, value);
            else if (node->left !=nullptr && node->right!=nullptr){
                node->data = _findMin(node->right)->data;
                _remove (node->right, node->data);
            }
            else{
                NodeBT<T>* nodetmp = node; //nodo a eliminar
                node = node->left!=nullptr ? node->left : node->right;
                delete nodetmp;
            }
        }

        bool _isfull(NodeBT<T>* node){
            
            if (node==nullptr) return true;
            if (node->left == nullptr && node->right == nullptr){
                return true;
            }
            if (node->left != nullptr && node->right != nullptr){
                return (_isfull(node->left) && _isfull(node->right));
            }
            return false;

        }

        int _size(NodeBT<T>* node){
            if (node == nullptr)
                return 0;
            else
                return (_size(node->left)+1+_size(node->right));
        }

        NodeBT<T>* _successor(NodeBT<T>* node, NodeBT<T>* succ,T value){

            if (node == nullptr) return succ;
            if (node->data == value){
                if (node->right!=nullptr) return _findMin(node->right);
            }
            else if (node->data < value){ //si esta value y su sucesor a la derecha
                return _successor(node->right, succ, value);
            }
            else { //si esta value y su sucesor a la izquierda voy guardando el padre en succesor
                succ = node;
                return _successor(node->left, succ, value);
            }
            return succ;

        }

        NodeBT<T>* _predecessor(NodeBT<T>* node, NodeBT<T>* prede,T value){

            if (node == nullptr) return prede;
            if (node->data == value){
                if (node->left!=nullptr) return _findMax(node->left);
            }
            else if (node->data < value){ //si esta value y su predecessor a la derecha voy guardando el padre en predecessor
                prede = node;
                return _predecessor(node->right, prede, value);
            }
            else { //si esta value y su predecessor a la izquierda                 
                return _predecessor(node->left, prede, value);
            }
            return prede;

        }

        NodeBT<T>* _buildFromOrderedArray(T arr[], int start, int end) {
            if (start > end) {
                return nullptr;
            }

            int mid = (start + end) / 2;
            NodeBT<T> *node = new NodeBT<T>(arr[mid]);

            node->left = _buildFromOrderedArray(arr, start, mid - 1);
            node->right = _buildFromOrderedArray(arr, mid + 1, end);

            return node;
        }

        void _displayDFS(NodeBT<T>* nodo, stringstream& ss) {
            if (nodo != nullptr) {
                ss << nodo->data << " ";
                _displayDFS(nodo->left, ss);
                _displayDFS(nodo->right, ss);
            }
        }

        void _findRange(NodeBT<T>* node,T valueStart, T valueEnd, vector<T> &result){
            if (node ==nullptr) return;

            if (valueStart < node->data  ) {
                _findRange (node->left, valueStart, valueEnd,result);
            }
            ///argrega valor
            if (valueStart <= node->data && valueEnd >= node->data){
                result.push_back(node->data);
            }
            if (valueEnd > node->data ) {
             _findRange (node->right, valueStart, valueEnd,result);
            }
        }

}; 


#endif


