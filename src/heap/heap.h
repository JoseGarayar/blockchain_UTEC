//
//  Heap.h
//  Heap
//
//  Created by Juan José Granados Moreno on 19/05/23.
//

#ifndef Heap_h
#define Heap_h

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class MaxHeap {
private:
    vector<T> heapArray;
    int heapSize;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;

        while (index > 0 && heapArray[index] > heapArray[parent]) {
            std::swap(heapArray[index], heapArray[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heapSize && heapArray[leftChild] > heapArray[largest])
            largest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild] > heapArray[largest])
            largest = rightChild;

        if (largest != index) {
            std::swap(heapArray[index], heapArray[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap() : heapSize(0) {}

    bool isEmpty() const {
        return heapSize == 0;
    }

    void insert(const T& item) {
        heapArray.push_back(item);
        heapSize++;
        heapifyUp(heapSize - 1);
    }

    T extractMax() {
        if (isEmpty())
            throw std::out_of_range("MaxHeap is empty");

        T maxItem = heapArray[0];
        std::swap(heapArray[0], heapArray[heapSize - 1]);
        heapSize--;
        heapifyDown(0);

        return maxItem;
    }
};

template <typename T>
class MinHeap {
private:
    vector<T> heapArray;
    int heapSize;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;

        while (index > 0 && heapArray[index] < heapArray[parent]) {
            std::swap(heapArray[index], heapArray[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heapSize && heapArray[leftChild] < heapArray[smallest])
            smallest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild] < heapArray[smallest])
            smallest = rightChild;

        if (smallest != index) {
            std::swap(heapArray[index], heapArray[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() : heapSize(0) {}

    bool isEmpty() const {
        return heapSize == 0;
    }

    void insert(const T& item) {
        heapArray.push_back(item);
        heapSize++;
        heapifyUp(heapSize - 1);
    }

    T extractMin() {
        if (isEmpty())
            throw std::out_of_range("MinHeap is empty");

        T minItem = heapArray[0];
        std::swap(heapArray[0], heapArray[heapSize - 1]);
        heapSize--;
        heapifyDown(0);

        return minItem;
    }
};




#endif /* Heap_h */
