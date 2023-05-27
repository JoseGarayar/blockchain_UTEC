
#include "src/blockchain.h"
//#include "hash_function.h"

int main() {
    Blockchain blockchain;

    std::vector<Transaction> transactions1;
    transactions1.push_back({1, "John", "Alice", 100.0, "2023-05-22"});
    transactions1.push_back({2, "Bob", "Carol", 50.0, "2023-05-23"});
    blockchain.addBlock(transactions1);

    std::vector<Transaction> transactions2;
    transactions2.push_back({3, "Alice", "Bob", 200.0, "2023-05-24"});
    blockchain.addBlock(transactions2);

    blockchain.displayChain();

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