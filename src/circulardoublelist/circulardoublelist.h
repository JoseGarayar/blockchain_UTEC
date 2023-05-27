#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H
#include "iteratorcirculardouble.h"

using namespace std;


template <typename T>
class CircularDoubleList{
   
private:
    NodeCircularDouble<T>* head;
    NodeCircularDouble<T>* tail;
    int nodes;

public:

    typedef CircularDoubleListIterator<T> iterator;
    
    CircularDoubleList() {
        head =  new NodeCircularDouble<T>();                
        head->prev = head;
        head->next = head;
        nodes=0;  
    }

    ~CircularDoubleList(){ 
        if (head!=nullptr) {
            _clear (head->next);
            //(head->prev)->next = nullptr;
            head -> killSelf();             
        }
    }

    T front(){
        if (empty()) throw out_of_range("Array is empty");
        return head->next->data;
    }

    T back(){
        if (empty()) throw out_of_range("Array is empty");
        return head->prev->data;
    }

    void push_front(T data){
       
       NodeCircularDouble<T>* nuevo = new NodeCircularDouble<T>();  //new NodeCircularDouble<T>(data);        
       nuevo ->data = data;
       nuevo -> next = head->next;
       nuevo -> prev = head;
    
       head->next->prev = nuevo;
       head -> next = nuevo;        
       nodes++;
    }

    void push_back(T data){

        NodeCircularDouble<T>* nuevo = new NodeCircularDouble<T>();  //new NodeCircularDouble<T>(data);        
        nuevo ->data = data;
        nuevo -> next = head;
        nuevo -> prev = head->prev;
       
        head->prev->next = nuevo;
        head -> prev = nuevo;        
        nodes++;

    }

    T pop_front(){
    
        if (empty()) throw out_of_range("Array is empty");

        NodeCircularDouble<T>* tmp = head->next;
        head->next = tmp ->next;
        tmp->next->prev = head;

        T deletedata = tmp->data;
        delete tmp;
        nodes--;
        return deletedata;

    }

    T pop_back(){

        if (empty()) throw out_of_range("Array is empty");

        NodeCircularDouble<T>* tmp = head->prev;
        head->prev = tmp ->prev;
        tmp->prev->next = head;

        T deletedata = tmp->data;
        delete tmp;
        nodes--;
        return deletedata;

    }


    void insert(T data, int index){

        NodeCircularDouble<T>* nodoactual = _searchIndex(index);

        NodeCircularDouble<T>* nuevo = new NodeCircularDouble<T>();  //new NodeCircularDouble<T>(data);        
        nuevo->data = data;
        nuevo->next = nodoactual;
        nuevo->prev = nodoactual->prev;

        nodoactual->prev->next = nuevo;
        nodoactual->prev = nuevo;
        nodes++;

    } 

    void remove(int index){

        NodeCircularDouble<T>* nodoactual = _searchIndex(index);
        nodoactual->prev->next = nodoactual->next;
        nodoactual->next->prev = nodoactual->prev;
        delete nodoactual;
        nodes--;

    }

    T& operator[ ](int index){

        return _searchIndex(index)->data;

    }


    bool empty(){
        return head== head->next;
    }

    int size(){
        return nodes;
    }
        
    void clear(){
        if (head == head->next){
            return;
        }
        _clear (head->next);
        head->next = head;
        head->prev = head;
        nodes=0;  
    }

    void reverse(){
        _reverse (head->next, head->prev);
    }

    iterator begin(){
        return iterator(head->next);      
    }

    iterator end(){
        return iterator(head);
    }   


private:

    void _clear(NodeCircularDouble <T>* nodo){
        if (nodo == head) return;
        _clear(nodo->next);        
        delete nodo;
    }

    void _reverse (NodeCircularDouble <T>* front, NodeCircularDouble <T>* back){
        
        if (front==back || front==head || back == head || back->next == front) return;
        _reverse (front->next, back->prev);
        swap (front->data, back->data);
    }

   
    NodeCircularDouble <T>* _searchIndex(int index){

        if (index>=nodes ) throw out_of_range("Index doesn't exist");
        
        if (nodes/2 > index) return  _searchIndexFront(index, head->next);
        else {            
            index = nodes - index -1;
            return  __searchIndexrBack(index, head->prev);
        }
        
    }

    NodeCircularDouble <T>* _searchIndexFront(int pos, NodeCircularDouble <T>* nodo){
        if (pos==0) return nodo;
        pos--;
        return  _searchIndexFront(pos, nodo->next);
    }

    NodeCircularDouble <T>* __searchIndexrBack(int pos, NodeCircularDouble <T>* nodo){
        if (pos==0) return nodo;
        pos--;
        return  __searchIndexrBack(pos, nodo->prev);
    }

};


#endif



