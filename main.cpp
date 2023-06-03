#include "src/blockchain.h"

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

    std::vector<Transaction> transactions3;
    transactions3.push_back({4, "Karl", "Bob", 250.0, "2023-05-26"});
    transactions3.push_back({5, "John", "Karl", 350.0, "2023-05-27"});
    blockchain.addBlock(transactions3);

    blockchain.displayChain();

    cout << "is valid? " << blockchain.validateChain() << endl;
    cout << endl;
    cout << endl;

    blockchain.deleteBlock(3);
    blockchain.displayChain();
    cout << "is valid? " << blockchain.validateChain() << endl;
    cout << endl;
    cout << endl;

    std::vector<Transaction> transactions4;
    transactions4.push_back({6, "Alice", "Martha", 50.0, "2023-05-27"});
    blockchain.updateDataBlock(0,transactions4);
    blockchain.displayChain();
    cout << "is valid? " << blockchain.validateChain() << endl;

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

    vec =  blockchain.findTransactionsByFromName("Alice"); 
    for(auto ele : vec) {        
            cout << "  ID Transaccion: " << ele.idTransaccion << endl;
            cout << "  Nombre 1: " << ele.nombreOrigen << endl;
            cout << "  Nombre 2: " << ele.nombreDestino << endl;
            cout << "  Importe: " << ele.importe << endl;
            cout << "  Fecha: " << ele.fecha << endl;
            cout << endl;                   
    }

    cout<< "Busqueda por Nombre Receptor" << endl;
    vec =  blockchain.findTransactionsByToName("Martha"); 
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