#include "nodecirculardouble.h"

template<class T>
class CircularDoubleListIterator{
    NodeCircularDouble <T>*  current; 
    
public:
    CircularDoubleListIterator(){
        
    } 

    CircularDoubleListIterator(NodeCircularDouble <T>*  current){
        
        this->current = current;
        //cout << current->data << endl;
    }


    bool operator!=(const CircularDoubleListIterator &other){
        //cout << "actual"<< this->current << "Final" <<  other.current << endl;
        return this->current != other.current;
    }

    CircularDoubleListIterator operator++(){
        
        current = current->next;
        return *this;
    }

    CircularDoubleListIterator operator--(){
        
        current = current->prev;
        return *this;
    }

    T operator*(){
        //cout << current->data << endl;
        return current->data;
    }
    
};