#include <iostream>
using namespace std;


template <typename T>
struct NodeCircularDouble {
    T data;
    NodeCircularDouble* next;
    NodeCircularDouble* prev;

    NodeCircularDouble(){ 
        next = nullptr;
        prev = nullptr;
    }

    NodeCircularDouble(T value){
        data = value;
    }

    void killSelf(){
        /*if (next != nullptr && next != this) {
            next->killSelf();
        }*/
        delete this;
    }    
};
