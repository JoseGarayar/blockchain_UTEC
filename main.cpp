
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
    transactions1.push_back({2, "Jose", "Carol", 50.0, "2023-05-23"});
    blockchain.addBlock(transactions1);

    std::vector<Transaction> transactions2;
    transactions2.push_back({4, "Jose", "Alice", 120.0, "2023-05-24"});
    transactions2.push_back({5, "Alice", "Bob", 100.0, "2023-05-24"});
    blockchain.addBlock(transactions2);

    displayChain(&blockchain);

    bool isvalid = blockchain.validateChain();
   
    cout<< isvalid << endl;

    cout<< "Busqueda por Rango" << endl;

    vector<Transaction> vec =  blockchain.findTransactionsByRangeof(100,120);
    for(auto ele : vec) {        
            cout << "  ID Transaccion: " << ele.idTransaccion << endl;
            cout << "  Nombre 1: " << ele.nombreOrigen << endl;
            cout << "  Nombre 2: " << ele.nombreDestino << endl;
            cout << "  Importe: " << ele.importe << endl;
            cout << "  Fecha: " << ele.fecha << endl;
            cout << endl;                   
    }

    cout<< "Busqueda por Nombre Emisor" << endl;

    vec =  blockchain.findTransactionsByFromName("Jose"); 
    for(auto ele : vec) {        
            cout << "  ID Transaccion: " << ele.idTransaccion << endl;
            cout << "  Nombre 1: " << ele.nombreOrigen << endl;
            cout << "  Nombre 2: " << ele.nombreDestino << endl;
            cout << "  Importe: " << ele.importe << endl;
            cout << "  Fecha: " << ele.fecha << endl;
            cout << endl;                   
    }

    cout<< "Busqueda por Nombre Receptor" << endl;
    vec =  blockchain.findTransactionsByToName("Alice"); 
    for(auto ele : vec) {        
            cout << "  ID Transaccion: " << ele.idTransaccion << endl;
            cout << "  Nombre 1: " << ele.nombreOrigen << endl;
            cout << "  Nombre 2: " << ele.nombreDestino << endl;
            cout << "  Importe: " << ele.importe << endl;
            cout << "  Fecha: " << ele.fecha << endl;
            cout << endl;                   
    }

    cout<< "Busqueda por Nombre Emison Inicia con " << endl;
    vec =  blockchain.findTransactionsByFromNameBeginWith("J"); 
    for(auto ele : vec) {        
            cout << "  ID Transaccion: " << ele.idTransaccion << endl;
            cout << "  Nombre 1: " << ele.nombreOrigen << endl;
            cout << "  Nombre 2: " << ele.nombreDestino << endl;
            cout << "  Importe: " << ele.importe << endl;
            cout << "  Fecha: " << ele.fecha << endl;
            cout << endl;                   
    }

}




/*
#include <iostream> 

// Funciones para las opciones del menú 
void opcion1() { 
    std::cout << "Opción 1 seleccionada." << std::endl; 
} 

void opcion2() { 
    std::cout << "Opción 2 seleccionada." << std::endl; 
} 

void opcion3() { 
    std::cout << "Opción 3 seleccionada." << std::endl; 
} 

void mostrarMenu() { 
    std::cout << "----- MENÚ ----- " << std::endl; 
    std::cout << "1. Opción 1" << std::endl; 
    std::cout << "2. Opción 2" << std::endl; 
    std::cout << "3. Opción 3" << std::endl; 
    std::cout << "0. Salir" << std::endl; 
    std::cout << "-----------------" << std::endl; 
    std::cout << "Seleccione una opción: "; 
} 

int main() { 
    int opcion; 
    while (true) { 
        mostrarMenu(); 
        std::cin >> opcion; 

        switch (opcion) { 
            case 1: 
                opcion1(); 
                break; 
            case 2: 
                opcion2(); 
                break; 
            case 3: 
                opcion3(); 
                break; 
            case 0: 
                std::cout << "Saliendo del programa..." << std::endl; 
                return 0; 
            default: 
                std::cout << "Opción inválida. Intente nuevamente." << std::endl; 
                break; 
        } 
        std::cout << std::endl; 
    } 

    return 0; 

}
*/