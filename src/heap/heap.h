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

template <typename Transactions>
class MaxHeap {
private:
    vector<Transactions> heapArray;
    int heapSize;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;

        while (index > 0 && heapArray[index].importe > heapArray[parent].importe) {
            swap(heapArray[index], heapArray[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heapSize && heapArray[leftChild].importe > heapArray[largest].importe)
            largest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild].importe > heapArray[largest].importe)
            largest = rightChild;

        if (largest != index) {
            swap(heapArray[index], heapArray[largest]);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap() : heapSize(0) {}

    bool isEmpty() const {
        return heapSize == 0;
    }

    void insert(const Transactions& item) {
        heapArray.push_back(item);
        heapSize++;
        heapifyUp(heapSize - 1);
    }

    Transactions extractMax() {
        if (isEmpty())
            throw out_of_range("MaxHeap is empty");

        Transactions maxItem = heapArray[0];
        swap(heapArray[0], heapArray[heapSize - 1]);
        heapSize--;
        heapifyDown(0);

        return maxItem;
    }
    
};

template <typename Transactions>
class MinHeap {
private:
    vector<Transactions> heapArray;
    int heapSize;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;

        while (index > 0 && heapArray[index].importe < heapArray[parent].importe) {
            swap(heapArray[index], heapArray[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heapSize && heapArray[leftChild].importe < heapArray[smallest].importe)
            smallest = leftChild;

        if (rightChild < heapSize && heapArray[rightChild].importe < heapArray[smallest].importe)
            smallest = rightChild;

        if (smallest != index) {
            swap(heapArray[index], heapArray[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() : heapSize(0) {}

    bool isEmpty() const {
        return heapSize == 0;
    }

    void insert(const Transactions& item) {
        heapArray.push_back(item);
        heapSize++;
        heapifyUp(heapSize - 1);
    }

    Transactions extractMin() {
        if (isEmpty())
            throw out_of_range("MinHeap is empty");

        Transactions minItem = heapArray[0];
        swap(heapArray[0], heapArray[heapSize - 1]);
        heapSize--;
        heapifyDown(0);

        return minItem;
    }
    
};

#endif /* Heap_h */
