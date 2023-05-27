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
    Blockchain() {
        Block* initialBlock = new Block(0, vector<Transaction>(), "0");
        blockchain.push_back(initialBlock);
        
    }

    void addBlock(const vector<Transaction>& data) {
        int index = blockchain.size();
        
        const string& previousHash = blockchain.back()->getHash();
        Block* newBlock = new Block(index, data, previousHash);
        blockchain.push_back(newBlock);
        

       /* for (const Transaction& transaction : data) {
            index[transaction.idTransaccion] = newBlock;
        }*/

        
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

    ~Blockchain() {
        blockchain.clear();
        /*for (auto& pair : index) {
            delete pair.second;
        }*/
    }
    
};