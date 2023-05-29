#include <iostream>
#include <forward_list>
#include <cmath>
using namespace std;

template<typename TK, typename TV>
class Pair {
public:
    TK first;
    TV second;

    Pair(const TK& f, const TV& s) : first(f), second(s) {}
};

template<typename TK, typename TV>
class ChainHash {
private:
    forward_list<Pair<TK, TV>> *array;
    int capacity;
    int size;
    int maxCollisions;
    float maxLoadFactor;
    hash<TK> hasher;
public:
    ChainHash(int cap = 13, int maxColl = 5, float maxLoad = 0.75) {
        this->capacity = cap;
        this->size = 0;
        this->maxCollisions = maxColl;
        this->maxLoadFactor = maxLoad;
        array = new forward_list<Pair<TK, TV>>[capacity];
    }
    
    void insert(const TK& first, const TV& second) {
        size_t hashcode = hasher(first);
        int index = hashcode % capacity;
        
        for (auto it = array[index].begin(); it != array[index].end(); ++it) {
            if (it->first == first) {
                return; 
            }
        }
        
        array[index].push_front(Pair<TK, TV>(first, second));
        size++;
        
        int collisions = countCollisions();
        if (collisions > maxCollisions) {
            rehash();
        }
        
        float loadFactor = static_cast<float>(size) / (capacity*maxCollisions);
        if (loadFactor > maxLoadFactor) {
            rehash();
        }
    }
    
    void remove(const TK& first) {
        size_t hashcode = hasher(first);
        int index = hashcode % capacity;
        
        array[index].remove_if([&](const Pair<TK, TV>& pair) {
            return pair.first == first;
        });
    }
    
    int bucket_count() {
        return capacity;
    }
    
    int bucket_size(int i) {
        return distance(array[i].begin(), array[i].end());
    }
    
    forward_list<Pair<TK, TV>>::iterator begin(int index) {
        return array[index].begin();
    }
    
    forward_list<Pair<TK, TV>>::iterator end(int index) {
        return array[index].end();
    }

    Pair<TK, TV>* find(const TK& first) {
        size_t hashcode = hasher(first);
        int index = hashcode % capacity;
        
        for (auto it = array[index].begin(); it != array[index].end(); ++it) {
            if (it->first == first) {
                return &(*it);
            }
        }
        
        cout << "No existe la clave: " << first << endl;
        return nullptr;
    }
    
private:
    int countCollisions() {
        int collisions = 0;
        for (int i = 0; i < capacity; i++) {
            if (bucket_size(i) > 1) {
                collisions += bucket_size(i) - 1;
            }
        }
        return collisions;
    }
    
    void rehash() {
        int newCapacity = ceil(capacity * 2.0);
        forward_list<Pair<TK, TV>> *newArray = new forward_list<Pair<TK, TV>>[newCapacity];
        
        for (int i = 0; i < capacity; i++) {
            for (auto it = array[i].begin(); it != array[i].end(); ++it) {
                size_t hashcode = hasher(it->first);
                int newIndex = hashcode % newCapacity;
                newArray[newIndex].push_front(Pair<TK, TV>(it->first, it->second));
            }
        }
        
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }
};
