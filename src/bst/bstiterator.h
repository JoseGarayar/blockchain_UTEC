#ifndef ITERATOR_H
#define ITERATOR_H
#include <stack>
#include <queue>
#include "bstnode.h"

enum class TypeBSTOrder{
        PreOrder, InOrder, PostOrder, BFS
    };


template <typename T>
class BSTIterator
{
public:
    
private:

    std::stack<NodeBT<T>*> nodes;
    std::queue<NodeBT<T>*> bfsQueue;
    TypeBSTOrder traversalOrder;

   /* NodeBT<T> *current;
    TypeBSTOrder type;
    stack<NodeBT<T>*> stackTree;*/

public:
    BSTIterator() : traversalOrder(TypeBSTOrder::InOrder) {};

    BSTIterator(NodeBT<T>* root, TypeBSTOrder order = TypeBSTOrder::InOrder) : traversalOrder(order) {
        pushAll(root);
    }
/*
    BSTIterator(NodeBT<T> *current,  TypeBSTOrder type=TypeBSTOrder::InOrder) {
        this->type = type;
        _fillStack(current, type);
        popstack();
    }
*/
    bool hasNext() {
        return !nodes.empty() || !bfsQueue.empty();
    }

    BSTIterator<T> &operator++() {
        if (traversalOrder == TypeBSTOrder::BFS) {
            NodeBT<T>* node = bfsQueue.front();
            bfsQueue.pop();
            pushAll(node->left);
            pushAll(node->right);
        } else {
            NodeBT<T>* node = nodes.top();
            nodes.pop();
            if (traversalOrder == TypeBSTOrder::InOrder)  pushAll(node->right);
            
            /*if (traversalOrder == TypeBSTOrder::InOrder) {
                pushAll(node->right);
            } else if (traversalOrder == TypeBSTOrder::PreOrder) {
                pushAll(node->right);
                pushAll(node->left);
            }*/
        }

        return *this;
    }

    T operator*() {
        if (traversalOrder == TypeBSTOrder::BFS) {
            return bfsQueue.front()->data;
        } else {
            return nodes.top()->data;
        }
    }

    bool operator!=(const BSTIterator<T>& other) const {
        if (traversalOrder == TypeBSTOrder::BFS && other.traversalOrder == TypeBSTOrder::BFS) {
            return !bfsQueue.empty() || !other.bfsQueue.empty();
        } else {
            return !nodes.empty() || !other.nodes.empty();
        }
    }

//    BSTIterator<T> &operator=(BSTIterator<T> other){};

/*    bool operator!=(BSTIterator<T> other){
        return this->current != other.current;
    }
*/


/*
    BSTIterator<T> &operator++(){
        popstack();
        return *this;
    }   //++it
    
    T operator*(){
        return current->data;
    }
*/
private:


    void pushAll(NodeBT<T>* node) {
        if (node == nullptr) {
            return;
        }

        if (traversalOrder == TypeBSTOrder::InOrder) {
            while (node != nullptr) {
                nodes.push(node);
                node = node->left;
            }
        } else if (traversalOrder == TypeBSTOrder::PreOrder) {
            pushAll(node->right);
            pushAll(node->left);
            nodes.push(node);
        } else if (traversalOrder == TypeBSTOrder::PostOrder) {
            std::stack<NodeBT<T>*> tempStack;
            tempStack.push(node);

            while (!tempStack.empty()) {
                NodeBT<T>* curr = tempStack.top();
                tempStack.pop();
                nodes.push(curr);

                if (curr->left) {
                    tempStack.push(curr->left);
                }
                if (curr->right) {
                    tempStack.push(curr->right);
                }
            }
        } else if (traversalOrder == TypeBSTOrder::BFS) {
            bfsQueue.push(node);
        }
    }

    /*void _fillStack(NodeBT<T>* node, TypeBSTOrder type){
       if (node ==nullptr) return;
       if (type== TypeBSTOrder::PreOrder){
            stackTree.push(node);
        }
        _fillStack(node->left, type);
        if (type== TypeBSTOrder::InOrder){
            stackTree.push(node);
        }
        _fillStack(node->right, type);
        if (type== TypeBSTOrder::PostOrder){
            stackTree.push(node);
        }
    }

    void popstack() {
          if (stackTree.empty()) current=nullptr;
        else {
            current = stackTree.top();
            stackTree.pop();
        }
    }*/

};

#endif