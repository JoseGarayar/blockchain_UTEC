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

    Blockchain() {
        Block* initialBlock = new Block(0, vector<Transaction>(), "0");
        blockchain.push_back(initialBlock);
        
    }

    void addBlock(vector<Transaction>& data) {
        int index = blockchain.size();
        
        const string& previousHash = blockchain.back()->getHash();
        Block* newBlock = new Block(index, data, previousHash);
        blockchain.push_back(newBlock);
        

       /* for (const Transaction& transaction : data) {
            index[transaction.idTransaccion] = newBlock;
        }*/

        // agrega los datos al indice BST
        for ( Transaction& transaction : data) {
            bstreeAmount->insert (transaction.importe, &transaction);
            bstreeFromName->insert (transaction.nombreOrigen, &transaction);
            bstreeToName->insert (transaction.nombreDestino, &transaction);
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

        CircularDoubleList<Block*>::iterator ite = blockchain.begin();

        for(; ite != blockchain.end(); ++ite){
            cout << "Index: " << (*ite)->getIndex() << endl;
            cout << "Transactions: " << endl;
            for (const Transaction& transaction : (*ite)->getData()) {
                cout << "  ID Transaccion: " << transaction.idTransaccion << endl;
                cout << "  Nombre 1: " << transaction.nombreOrigen << endl;
                cout << "  Nombre 2: " << transaction.nombreDestino << endl;
                cout << "  Importe: " << transaction.importe << endl;
                cout << "  Fecha: " << transaction.fecha << endl;
                cout << endl;
            }
            
            cout << "Previous Hash: " << (*ite)->getPreviousHash() << endl;
            cout << "Hash: " << (*ite)->getHash() << endl;
            cout << endl;
        }

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