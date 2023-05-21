#include <openssl/evp.h>
#include <openssl/sha.h>

#include <iostream> 
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

string calculateHash(const string& data) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    // Selecciona el algoritmo de hash (en este caso, SHA-256)
    md = EVP_sha256();

    // Crea el contexto del hash
    mdctx = EVP_MD_CTX_new();

    // Inicializa el cálculo del hash
    EVP_DigestInit_ex(mdctx, md, NULL);

    // Actualiza el cálculo del hash con los datos
    EVP_DigestUpdate(mdctx, data.c_str(), data.length());

    // Finaliza el cálculo del hash y obtiene el resultado
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // Limpia y libera los recursos
    EVP_MD_CTX_free(mdctx);

    // Convierte el hash a una cadena hexadecimal
    stringstream ss;
    for (unsigned int i = 0; i < hash_len; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

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

// How to compile
// g++ -o main main.cpp -lssl -lcrypto
// ./main