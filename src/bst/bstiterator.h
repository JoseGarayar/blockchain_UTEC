#ifndef ITERATOR_H
#define ITERATOR_H
#include <stack>
#include <queue>
#include "bstnode.h"

enum class TypeBSTOrder{
        PreOrder, InOrder, PostOrder, BFS
    };


template<typename TK, typename TV>
class BSTIterator
{
public:
    
private:

    std::stack<NodeBT<TK,TV>*> nodes;
    std::queue<NodeBT<TK,TV>*> bfsQueue;
    TypeBSTOrder traversalOrder;

public:
    BSTIterator() : traversalOrder(TypeBSTOrder::InOrder) {};

    BSTIterator(NodeBT<TK, TV>* root, TypeBSTOrder order = TypeBSTOrder::InOrder) : traversalOrder(order) {
        pushAll(root);
    }

    bool hasNext() {
        return !nodes.empty() || !bfsQueue.empty();
    }

    BSTIterator<TK,TV> &operator++() {
        if (traversalOrder == TypeBSTOrder::BFS) {
            NodeBT<TK,TV>* node = bfsQueue.front();
            bfsQueue.pop();
            pushAll(node->left);
            pushAll(node->right);
        } else {
            NodeBT<TK,TV>* node = nodes.top();
            nodes.pop();
            if (traversalOrder == TypeBSTOrder::InOrder)  pushAll(node->right);
            
        }

        return *this;
    }

    TK operator*() {
        if (traversalOrder == TypeBSTOrder::BFS) {
            return bfsQueue.front()->key;
        } else {
            return nodes.top()->key;
        }
    }

    bool operator!=(const BSTIterator<TK,TV>& other) const {
        if (traversalOrder == TypeBSTOrder::BFS && other.traversalOrder == TypeBSTOrder::BFS) {
            return !bfsQueue.empty() || !other.bfsQueue.empty();
        } else {
            return !nodes.empty() || !other.nodes.empty();
        }
    }


private:


    void pushAll(NodeBT<TK,TV>* node) {
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
            std::stack<NodeBT<TK,TV>*> tempStack;
            tempStack.push(node);

            while (!tempStack.empty()) {
                NodeBT<TK,TV>* curr = tempStack.top();
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


};

#endif