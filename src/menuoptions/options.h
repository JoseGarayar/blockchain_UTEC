
#include "../blockchain.h"
#include "../CSV/CSVManager.h"
#include "../console/consolewriter.h"




void _displaychain (Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"OPCION 2 - Generar Blockchain desde archivo .csv");

    Blockchain::iterator ite = blockchain.begin();
    int row= 4;
    for(; ite != blockchain.end(); ++ite){
        std::string ss = "Index: " + std::to_string( (*ite)->getIndex() );
        writer.write(++row, 5, ss);
        ss = "Nonce: " + std::to_string( (*ite)-> getNonce() );
        writer.write(++row, 5, ss);
        writer.write(++row, 5, "Transactions: ");
        for (const Transaction& transaction : (*ite)->getData()) {
            ss = "ID Transaccion: " + std::to_string( transaction.idTransaccion );
            writer.write(++row, 10, ss);
            ss = "Nombre 1:" +  transaction.nombreOrigen;
            writer.write(++row, 10, ss);
            ss = "Nombre 2:" +  transaction.nombreDestino;
            writer.write(++row, 10, ss);
            ss = "Importe: " + std::to_string( transaction.importe );
            writer.write(++row, 10, ss);
            ss = "Fecha:" +  transaction.fecha;
            writer.write(++row, 10, ss);
        }
        ss = "Previous Hash: " +  (*ite)-> getPreviousHash() ;
        writer.write(++row, 5, ss);
        ss = "Hash: " +  (*ite)-> getHash() ;
        writer.write(++row, 5, ss);
        if (row >25 ){

            writer.write(25,10,"Presione una tecla para continuar o ESC para regresar a menu");
            char x = writer.getchr();
            if (x = KEY_EXIT){
                break;
            }
            writer.clearScreen();
            row = 4;
        }
    }
    writer.getchr();

}


void opcion1InsertarBloque(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();

}

void opcion2CargarArchivo(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"OPCION 2 - Generar Blockchain desde archivo .csv");
    writer.write(5,10,"Presione una tecla para cargar archivo /src/CSV/transactions.csv");

    writer.getchr();
    
    int nroRegPorBloque= 5;


    CSVManager manager;
    vector<vector<string>> rows = manager.readFile("src/CSV/transactions.csv");

    int nrotransenbloque=0;
    std::vector<Transaction> transactions1;

    for (vector<string> column: rows) {
        transactions1.push_back({std::stoi(column[0]), column[1] , column[2], std::stod(column[4]), column[3]});
        if(nrotransenbloque<nroRegPorBloque-1){            
            nrotransenbloque++;
        }
        else{
            blockchain.addBlock(transactions1);
            nrotransenbloque=0;
            transactions1.clear();
        }        
        //cout << column[0] + "\t" + column[1] + "\t" + column[2] + "\t" + column[3] + "\t" + column[4] << endl;
    }
    if (!transactions1.empty()){
         blockchain.addBlock(transactions1);
    }

    _displaychain(blockchain,writer);
    
}

void displayBlock(Block block) {
        
}