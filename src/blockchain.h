#include "block.h"
#include <list>
#include <unordered_map>
#include "circulardoublelist/circulardoublelist.h"

using namespace std;

class Blockchain {
private:
    
    CircularDoubleList<Block*> blockchain;
    unordered_map<int, Block*> index;

public:
    typedef CircularDoubleListIterator<Block*> iterator;

    Blockchain() {}

    void addBlock(const vector<Transaction>& data) {
        int index = blockchain.size();
        const string& previousHash = index != 0 ? blockchain.back()->getHash() : defaultHash();
        Block* newBlock = new Block(index, data, previousHash);
        blockchain.push_back(newBlock);        

        /* Agregar insercion en estructuras de indices
        for (const Transaction& transaction : data) {
            index[transaction.idTransaccion] = newBlock;
        }*/

    }

    void deleteBlock(int index) {
        if (index < 0 || index >= blockchain.size()) {
            cout << "El bloque no existe" << endl;
            return;
        }
        blockchain.remove(index);
        cascadeEffect();
        /*
            Agregar eliminacion en estructuras de indices
        */
    }

    void updateDataBlock(int index, const vector<Transaction>& data) {
        if (index < 0 || index >= blockchain.size()) {
            cout << "El bloque no existe" << endl;
            return;
        }
        if (index == 0) {
            blockchain[index]->update_block(index, data, defaultHash());
        } else {
            blockchain[index]->update_block(index, data, blockchain[index-1]->getHash());
        }
        cascadeEffect();
        /*
            Agregar actualizacion en estructuras de indices
        */
    }

    void cascadeEffect() {
        CircularDoubleList<Block*>::iterator ite = blockchain.begin();
        CircularDoubleList<Block*>::iterator ite_prev = blockchain.begin();
        int i = 0;
        for(; ite != blockchain.end(); ++ite){
            if (i == 0) {
                (*ite)->update_block(i, (*ite)->getData(), defaultHash());
                ite_prev = ite;
            } else {
                (*ite)->update_block(i, (*ite)->getData(), (*ite_prev)->getHash());
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

    Block* findBlockByTransactionId(int idTransaccion) {
        auto it = index.find(idTransaccion);
        if (it != index.end()) {
            return it->second;
        }
        return nullptr;
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

    ~Blockchain() {
        blockchain.clear();
        /*for (auto& pair : index) {
            delete pair.second;
        }*/
    }
    
};