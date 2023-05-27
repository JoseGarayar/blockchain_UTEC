
#include "src/blockchain.h"
//#include "hash_function.h"

void displayChain(Blockchain* blockchain)  {

    Blockchain::iterator ite = blockchain->begin();

    for(; ite != blockchain->end(); ++ite){
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


int main() {
    Blockchain blockchain;

    std::vector<Transaction> transactions1;
    transactions1.push_back({1, "John", "Alice", 100.0, "2023-05-22"});
    transactions1.push_back({2, "Bob", "Carol", 50.0, "2023-05-23"});
    blockchain.addBlock(transactions1);

    std::vector<Transaction> transactions2;
    transactions2.push_back({3, "Alice", "Bob", 200.0, "2023-05-24"});
    blockchain.addBlock(transactions2);

    displayChain(&blockchain);

    bool isvalid = blockchain.validateChain();
   
    cout<< isvalid << endl;
}




/*
int main() {
    string data = "Hello, world! Test";
    string hash = "1234";
    string prev = "0000000000000000000000000000000000000000000000000000000000000000";
    int block_num = 0;
    int nonce = 0;
    while (hash.substr(0,4) != "0000") {
        hash = calculateHash(to_string(block_num) + to_string(nonce) + data + prev);
        nonce++;
    }
    nonce--;
    cout << "Hash: " << hash << endl;
    cout << "Nonce: " << nonce << endl;

    return 0;
}
*/