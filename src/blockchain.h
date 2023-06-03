#include "block.h"
#include <list>
#include <unordered_map>
#include "circulardoublelist/circulardoublelist.h"
#include "bst/bst.h"

using namespace std;

class Blockchain {
private:
    
    CircularDoubleList<Block*> blockchain;
    unordered_map<int, Block*> index;
    //indice BST para los importes
    BSTree<double, Transaction*> *bstreeAmount = new BSTree<double, Transaction*>();
    //indice BST para los NombreEmisor
    BSTree<string, Transaction*> *bstreeFromName = new BSTree<string, Transaction*>();
    //indice BST para los nombrereceptor
    BSTree<string, Transaction*> *bstreeToName = new BSTree<string, Transaction*>();

public:
    typedef CircularDoubleListIterator<Block*> iterator;

    Blockchain() {}

    void addBlock(vector<Transaction>& data) {
        int index = blockchain.size();
        const string& previousHash = index != 0 ? blockchain.back()->getHash() : defaultHash();
        Block* newBlock = new Block(index, data, previousHash);
        blockchain.push_back(newBlock);        

        /* Agregar insercion en estructuras de indices
        for (const Transaction& transaction : data) {
            index[transaction.idTransaccion] = newBlock;
        }*/

        // agrega los datos al indice BST
        for ( Transaction& transaction : data) {
            bstreeAmount->insert (transaction.importe, &transaction);
            bstreeFromName->insert (transaction.nombreOrigen, &transaction);
            bstreeToName->insert (transaction.nombreDestino, &transaction);
        }
        
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

    vector<Transaction> findTransactionsByRangeof(double amountIni, double amountEnd){

        vector<Transaction> result;
        vector<pair<double, Transaction*>> arr = bstreeAmount->findRange(amountIni,amountEnd);
        for(auto ele : arr) {        
            result.push_back( *ele.second);                    
        }
        return result;
    }

    vector<Transaction> findTransactionsByFromName(string name){

        vector<Transaction> result;
        vector<pair<string, Transaction*>> arr = bstreeFromName->findKey(name);
        for(auto ele : arr) {        
            result.push_back( *ele.second);                    
        }
        return result;
    }

    vector<Transaction> findTransactionsByToName(string name){

        vector<Transaction> result;
        vector<pair<string, Transaction*>> arr = bstreeToName->findKey(name);
        for(auto ele : arr) {        
            result.push_back( *ele.second);                    
        }
        return result;
    }

    vector<Transaction> findTransactionsByFromNameBeginWith(string name){

        vector<Transaction> result;
        vector<pair<string, Transaction*>> arr = bstreeFromName->findKeyBeginWith(name);
        for(auto ele : arr) {        
            result.push_back( *ele.second);                    
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

    ~Blockchain() {
        blockchain.clear();
        /*for (auto& pair : index) {
            delete pair.second;
        }*/
    }
    
};