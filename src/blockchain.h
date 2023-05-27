#include "block.h"
#include <list>
#include <unordered_map>


class Blockchain {
private:
    std::list<Block> chain;
    std::unordered_map<int, Block*> index;

public:
    Blockchain() {
        Block genesisBlock(0, std::vector<Transaction>(), "0");
        chain.push_back(genesisBlock);
    }

    void addBlock(const std::vector<Transaction>& data) {
        int index = chain.size();
        const std::string& previousHash = chain.back().getHash();
        Block* newBlock = new Block(index, data, previousHash);
        chain.push_back(*newBlock);

       /* for (const Transaction& transaction : data) {
            index[transaction.idTransaccion] = newBlock;
        }*/

        
    }

    bool validateChain() const {
        
        /*auto it = std::next(chain.begin());
        auto prevIt = chain.begin();

        while (it != chain.end()) {
            const Block& currentBlock = *it;
            const Block& previousBlock = *prevIt;

            if (currentBlock.proofOfWork()) return false;

            if (currentBlock.getHash() != currentBlock.calculateHash(currentBlock.getData(), currentBlock.getPreviousHash(),  currentBlock.getnonce())) {
                return false;
            }

            if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
                return false;
            }

            ++it;
            ++prevIt;
        }
            */
        return true;
    }

    Block* findBlockByTransactionId(int idTransaccion) {
        auto it = index.find(idTransaccion);
        if (it != index.end()) {
            return it->second;
        }
        return nullptr;
    }

    void displayChain() const {
        for (const Block& block : chain) {
            std::cout << "Index: " << block.getIndex() << std::endl;
            std::cout << "Transactions: " << std::endl;
            for (const Transaction& transaction : block.getData()) {
                std::cout << "  ID Transaccion: " << transaction.idTransaccion << std::endl;
                std::cout << "  Nombre 1: " << transaction.nombreOrigen << std::endl;
                std::cout << "  Nombre 2: " << transaction.nombreDestino << std::endl;
                std::cout << "  Importe: " << transaction.importe << std::endl;
                std::cout << "  Fecha: " << transaction.fecha << std::endl;
                std::cout << std::endl;
            }
            
            std::cout << "Previous Hash: " << block.getPreviousHash() << std::endl;
            std::cout << "Hash: " << block.getHash() << std::endl;
            std::cout << std::endl;
        }
    }

    ~Blockchain() {
        for (auto& pair : index) {
            delete pair.second;
        }
    }
    
};