#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>
#include <iomanip>

using namespace std;

struct Transaction {
    int idTransaccion;
    string nombreOrigen;
    string nombreDestino;
    double importe;
    string fecha;
};

class Block {
private:
    int index;
    vector<Transaction> data;
    string previousHash;
    string hash;
    int nonce;
    
   

public:
    Block(int index, const vector<Transaction>& data, const string& previousHash) {
        this->index = index;
        this->data = data;
        this->previousHash = previousHash;        
        this->nonce = 0;
        this->hash = mineBlock();
    
    }

    int getIndex() const {
        return index;
    }

    int getNonce() const {
        return nonce;
    }

    vector<Transaction> getData() const {
        return data;
    }

    string getPreviousHash() const {
        return previousHash;
    }

    string getHash() const {
        return hash;
    }

    string mineBlock() {
        string targetPrefix = "0000";
        while (true) {
            hash = calculateHash(index, data, previousHash, nonce);
            if (hash.substr(0,4) == targetPrefix) {
                return hash;
            }
            nonce++;
        }
    }

    string calculateHash(int index, const vector<Transaction>& data, const string& previousHash, int nonce) const {
        stringstream ss;
        ss << index;
        for (const Transaction& transaction : data) {
            ss << transaction.idTransaccion << transaction.nombreOrigen << transaction.nombreDestino << transaction.importe << transaction.fecha;
        }
        ss << previousHash << nonce << index;

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, ss.str().c_str(), ss.str().size());
        SHA256_Final(hash, &sha256);

        stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashStream << hex << setw(2) << setfill('0') << (int)hash[i];
        }

        return hashStream.str();
    }

    bool isValid(){
        return (this->hash==mineBlock());
    }

    void update_block(int index, const vector<Transaction>& data, const string& previousHash) {
        this->index = index;
        this->data = data;
        this->previousHash = previousHash;
        this->hash = mineBlock();
    }

    void displayBlock() {
        cout << "Index: " << getIndex() << endl;
        cout << "Nonce: " << getNonce() << endl;
        cout << "Transactions: " << endl;
        for (const Transaction& transaction : getData()) {
            cout << "  ID Transaccion: " << transaction.idTransaccion << endl;
            cout << "  Nombre 1: " << transaction.nombreOrigen << endl;
            cout << "  Nombre 2: " << transaction.nombreDestino << endl;
            cout << "  Importe: " << transaction.importe << endl;
            cout << "  Fecha: " << transaction.fecha << endl;
            cout << endl;
        }
        cout << "Previous Hash: " << getPreviousHash() << endl;
        cout << "Hash: " << getHash() << endl;
        cout << endl;
    }

};