
#include "../blockchain.h"
#include "../CSV/CSVManager.h"
#include "../console/consolewriter.h"


void opcion1InsertarBloque(Blockchain & blockchain, ConsoleWriter writer){

    int row= 4;
    int ntran =0;
    vector<Transaction> transaction;
    writer.clearScreen();
    writer.write(2,10,"INSERTAR BLOQUE");

    writer.write(4,5,"Indicar el número de transacciones a ingresar");
    ntran = writer.readInt();
    for (int i=1; i<= ntran;i++ ){

    }


}

void displaychain (Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    

    Blockchain::iterator ite = blockchain.begin();
    int row= 4;
    
    while (ite != blockchain.end()) {
        writer.write(2,10,"Mostrar Blockchain");

        std::string ss = "Index: " + std::to_string( (*ite)->getIndex() );
        writer.write(++row, 5, ss);
        ss = "Nonce: " + std::to_string( (*ite)-> getNonce() );
        writer.write(++row, 5, ss);
        writer.write(++row, 5, "Transactions: ");
        for (const Transaction& transaction : (*ite)->getData()) {
            ss = "ID Transaccion: " + std::to_string( transaction.idTransaccion );
            writer.write(++row, 10, ss);
            ss = "Nombre Emisor:" +  transaction.nombreOrigen;
            writer.write(++row, 10, ss);
            ss = "Nombre Receptor:" +  transaction.nombreDestino;
            writer.write(row, 40, ss);
            ss = "Importe: " + std::to_string( transaction.importe );
            writer.write(++row, 10, ss);
            ss = "Fecha:" +  transaction.fecha;
            writer.write(row, 40, ss);
        }
        ss = "Previous Hash: " +  (*ite)-> getPreviousHash() ;
        writer.write(++row, 5, ss);
        ss = "Hash: " +  (*ite)-> getHash() ;
        writer.write(++row, 5, ss);

        writer.write(row+4,5,"Presione una tecla [<] para retroceder [>] para avanzar o [Q] para regresar a menu");
        int x = writer.getwchr();
        switch( x ) {
            case KEY_UP:
                --ite;
                break;
            case KEY_LEFT:
                --ite;
                break;
            case KEY_DOWN:
                ++ite;
                break;
            case KEY_RIGHT:
                ++ite;
                break;
            case 113:
                return;
                break;
            case 21:
                return;
                break;            
        }
        if (x == KEY_EXIT){
            break;
        }
        writer.clearScreen();
        row = 4;
        
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
    blockchain.clear();

    CSVManager manager;
    vector<vector<string>> rows = manager.readFile("src/CSV/transactions.csv");

    int nrotransenbloque=0;
    std::vector<Transaction> transactions1;
    int i=0;
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
        std::string ss = "Cargando "+ std::to_string(i)+ " de "+ std::to_string(rows.size())+" transacciones.";
        writer.write(20,10,ss);
        i++;
    }
    if (!transactions1.empty()){
         blockchain.addBlock(transactions1);
    }

    displaychain(blockchain,writer);
    
}

