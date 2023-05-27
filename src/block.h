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
        string target = targetPrefix + string(SHA256_DIGEST_LENGTH / 2 - targetPrefix.size(), '0');

        while (true) {
            hash = calculateHash(data, previousHash, nonce);

            if (hash.substr(0, targetPrefix.size()) == targetPrefix) {
                return hash;
            }

            nonce++;
        }
    }

     string calculateHash(const vector<Transaction>& data, const string& previousHash,  int nonce) const {
        stringstream ss;
        for (const Transaction& transaction : data) {
            ss << transaction.idTransaccion << transaction.nombreOrigen << transaction.nombreDestino << transaction.importe << transaction.fecha;
        }
        ss << previousHash << nonce;

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

    bool proofOfWork(){

        return (this->hash==mineBlock());
    }

};