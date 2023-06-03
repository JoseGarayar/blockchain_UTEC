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
    BSTree<double, int > *bstreeAmount = new BSTree<double, int>();
    //indice BST para los NombreEmisor
    BSTree<string, int > *bstreeFromName = new BSTree<string, int>();
    //indice BST para los nombrereceptor
    BSTree<string, int > *bstreeToName = new BSTree<string, int >();

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
            bstreeAmount->insert (transaction.importe, index);
            bstreeFromName->insert (transaction.nombreOrigen, index);
            bstreeToName->insert (transaction.nombreDestino, index);
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
            bstreeAmount->remove(transaction.importe);
            bstreeFromName->remove(transaction.nombreOrigen);
            bstreeToName->remove(transaction.nombreDestino);
        }

        blockchain.remove(index);
        cascadeEffect();
        
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
        for(Transaction ele : blockchain[index]->getData()) { 
            bstreeAmount->remove(ele.importe);
            bstreeFromName->remove(ele.nombreOrigen);
            bstreeToName->remove(ele.nombreDestino);  

            bstreeAmount->insert (ele.importe, index);
            bstreeFromName->insert (ele.nombreOrigen, index);
            bstreeToName->insert (ele.nombreDestino, index);
        }
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
        vector<pair<double, int>> arr = bstreeAmount->findRange(amountIni,amountEnd);

        for (int i= 0; i< arr.size(); i++){
            for(Transaction ele : blockchain[arr[i].second]->getData()) { 
                if (ele.importe >= amountIni && ele.importe <=amountEnd){
                    result.push_back(ele);
                } 
            }
        }
        return result;
    }

    vector<Transaction> findTransactionsByFromName(string name){

        vector<Transaction> result;
        vector<pair<string, int>> arr = bstreeFromName->findKey(name);

        for (int i= 0; i< arr.size(); i++){
            for(Transaction ele : blockchain[arr[i].second]->getData()) { 
                if (ele.nombreOrigen==name){
                    result.push_back(ele);
                } 
            }
        }
        return result;
    }

    vector<Transaction> findTransactionsByToName(string name){

        vector<Transaction> result;
        vector<pair<string, int>> arr = bstreeToName->findKey(name);

        for (int i= 0; i< arr.size(); i++){
            for(Transaction ele : blockchain[arr[i].second]->getData()) { 
                if (ele.nombreOrigen==name){
                    result.push_back(ele);
                } 
            }
        }
        return result;
    }

    vector<Transaction> findTransactionsByFromNameBeginWith(string name){

        vector<Transaction> result;
        vector<pair<string, int>> arr = bstreeFromName->findKeyBeginWith(name);
         for (int i= 0; i< arr.size(); i++){
            for(Transaction ele : blockchain[arr[i].second]->getData()) { 
                if (ele.nombreOrigen.substr(0,name.size())==name){
                    result.push_back(ele);
                } 
            }
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