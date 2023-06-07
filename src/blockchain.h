#include "block.h"
// #include <list>
// #include <unordered_map>
#include "circulardoublelist/circulardoublelist.h"
#include "bst/bst.h"
#include "hashtable/hashtable.h"
#include "heap/heap.h"

using namespace std;

class Blockchain {
private:
    
    CircularDoubleList<Block*> blockchain;
    //indice BST para fechas
    BSTree<string, pair<int,int> > *bstreeDates = new BSTree<string, pair<int,int> >();
    //indice BST para los NombreEmisor
    BSTree<string, pair<int,int>  > *bstreeFromName = new BSTree<string, pair<int,int> >();
    //indice BST para los nombrereceptor
    BSTree<string, pair<int,int>  > *bstreeToName = new BSTree<string, pair<int,int>  >();
    //indice Hash Table para NombreEmisor (igual a X) 
    HashTable<string, Pair<int, int> > hashTableFromName;
    //indice Hash Table para NombreReceptor (igual a X) 
    HashTable<string, Pair<int, int> > hashTableToName;
    // índice maxheap
    MaxHeap<Transaction> maxHeap;
    // índice minheap
    MinHeap<Transaction> minHeap;

public:
    typedef CircularDoubleListIterator<Block*> iterator;

    Blockchain() {}

    void addBlock(vector<Transaction>& data) {
        int index = blockchain.size();
        const string& previousHash = index != 0 ? blockchain.back()->getHash() : defaultHash();
        Block* newBlock = new Block(index, data, previousHash);
        blockchain.push_back(newBlock);        

        // Agregar insercion en estructuras de indices
        // agrega los datos al indice BST
    
        int i = 0; 
        for ( Transaction& transaction : data) {
            // BST
            bstreeDates->insert (transaction.fecha, make_pair(index, i));
            bstreeFromName->insert (transaction.nombreOrigen, make_pair(index, i));
            bstreeToName->insert (transaction.nombreDestino, make_pair(index, i));
            // Hash Table
            hashTableFromName.insert(transaction.nombreOrigen, Pair<int, int>(index, i));
            hashTableToName.insert(transaction.nombreDestino, Pair<int, int>(index, i));
            i++;

            maxHeap.insert(transaction);
            minHeap.insert(transaction);
        }
        
    }

    void deleteBlock(int index) {
        if (index < 0 || index >= blockchain.size()) {
            cout << "El bloque no existe" << endl;
            return;
        }

        /*
            Agregar eliminacion en estructuras de indices
        */
        Block* block = blockchain[index];
        for ( Transaction& transaction : block->getData()) {
            // BST
            bstreeDates->remove(transaction.fecha);
            bstreeFromName->remove(transaction.nombreOrigen);
            bstreeToName->remove(transaction.nombreDestino);
            // Hash Table
            hashTableFromName.remove(transaction.nombreOrigen);
            hashTableToName.remove(transaction.nombreDestino);

            maxHeap.deleteNode(transaction);
            minHeap.deleteNode(transaction);            
        }

        blockchain.remove(index);
        cascadeEffect();
        
    }

    void deleteNodeFromHeap(int index) {
        if (index < 0 || index >= blockchain.size()) {
            cout << "El bloque no existe" << endl;
            return;
        }

        Block* block = blockchain[index];
        maxHeap.deleteNode(block->getData()[0]);
        minHeap.deleteNode(block->getData()[0]);
    }

    void updateDataBlock(int index, const vector<Transaction>& data) {
        if (index < 0 || index >= blockchain.size()) {
            cout << "El bloque no existe" << endl;
            return;
        }

        /*
            Eliminación indice anterior
        */
        int i=0;
        for(Transaction ele : blockchain[index]->getData()) {  
            // BST           
            bstreeDates->remove(ele.fecha);
            bstreeFromName->remove(ele.nombreOrigen);
            bstreeToName->remove(ele.nombreDestino);
            // Hash Table
            hashTableFromName.remove(ele.nombreOrigen);
            hashTableToName.remove(ele.nombreDestino);
            // Max y Min Heap
            maxHeap.deleteNode(ele);
            minHeap.deleteNode(ele);
        }

        if (index == 0) {
            blockchain[index]->update_block(index, data, defaultHash());
        } else {
            blockchain[index]->update_block(index, data, blockchain[index-1]->getHash());
        }
        cascadeEffect();
        /*
            Agregar nuevos indices
        */
        i=0;
        for(Transaction ele : blockchain[index]->getData()) {             
            // BST
            bstreeDates->insert (ele.fecha, make_pair(index, i));
            bstreeFromName->insert (ele.nombreOrigen, make_pair(index, i));
            bstreeToName->insert (ele.nombreDestino, make_pair(index, i));
            // Hash Table
            hashTableFromName.insert(ele.nombreOrigen, Pair<int, int>(index, i));
            hashTableToName.insert(ele.nombreDestino, Pair<int, int>(index, i));
            // Max y Min Heap
            maxHeap.insert(ele);
            minHeap.insert(ele);
        }
    }

    void cascadeEffect(bool mine = false) {
        CircularDoubleList<Block*>::iterator ite = blockchain.begin();
        CircularDoubleList<Block*>::iterator ite_prev = blockchain.begin();
        int i = 0;
        for(; ite != blockchain.end(); ++ite){
            if (i == 0) {
                (*ite)->update_block(i, (*ite)->getData(), defaultHash(), mine=mine);
                ite_prev = ite;
            } else {
                (*ite)->update_block(i, (*ite)->getData(), (*ite_prev)->getHash(), mine=mine);
                ++ite_prev;
            }
            i++;
        }
    }

    bool validateChain()  {
        
        CircularDoubleList<Block*>::iterator ite = blockchain.begin();

        Block*  previousBlock = *ite;
        ++ite;
        for(; ite != blockchain.end(); ++ite){
            Block* currentBlock = *ite;
            if (!currentBlock->isValid()) return false;
            if (currentBlock->getPreviousHash() != previousBlock->getHash()) return false;
            previousBlock = *ite;
        }
        
        return true;
    }

    // Complejidad O(1)
    Transaction findMaxTransaction() {
        return maxHeap.extractMax();
    }

    // Complejidad O(1)
    Transaction findMinTransaction() {
        return minHeap.extractMin();
    }

    vector<Transaction> findTransactionsByRangeof(string dateIni, string dateEnd){

        vector<Transaction> result;
        vector<pair<string, pair<int, int>>> arr = bstreeDates->findRange(dateIni,dateEnd);

        for(auto ele : arr) { 
             result.push_back(blockchain[ele.second.first]->getData()[ele.second.second]);
        }

        return result;
    }

    vector<Transaction> findTransactionsByFromName(string name){
        vector<Transaction> result;
        forward_list<Pair<int, int>> forwardListFromName = hashTableFromName.find(name);
        for(auto ele : forwardListFromName) { 
             result.push_back(blockchain[ele.first]->getData()[ele.second]);
        }
        return result;
    }

    vector<Transaction> findTransactionsByToName(string name){
        vector<Transaction> result;
        forward_list<Pair<int, int>> forwardListToName = hashTableToName.find(name);
        for(auto ele : forwardListToName) { 
             result.push_back(blockchain[ele.first]->getData()[ele.second]);
        }
        return result;
    }

    vector<Transaction> findTransactionsByFromNameBeginWith(string name){

        vector<Transaction> result;        
        vector<pair<string, pair<int, int>>> arr = bstreeFromName->findKeyBeginWith(name);
        for(auto ele : arr) { 
             result.push_back(blockchain[ele.second.first]->getData()[ele.second.second]);
        }

        return result;
        
    }

    void displayChain()  {
        CircularDoubleList<Block*>::iterator ite = begin();
        for(; ite != end(); ++ite){
            (*ite)->displayBlock();
        }
    }

    string defaultHash() {
        string defaultHash = string(64, '0');
        return defaultHash;
    }

    iterator begin(){
        return blockchain.begin();      
    }

    iterator end(){
        return blockchain.end();
    }   

    void clear(){
        blockchain.clear();
    }

    ~Blockchain() {
        blockchain.clear();
        /*for (auto& pair : index) {
            delete pair.second;
        }*/
    }
    
};