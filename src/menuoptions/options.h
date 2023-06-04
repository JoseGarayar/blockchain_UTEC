
#include "../blockchain.h"
#include "../CSV/CSVManager.h"
#include "../console/consolewriter.h"

void opcionBuscarRangoFechas(Blockchain & blockchain, ConsoleWriter writer){

    string fechaIni, fechaFin;

    writer.clearScreen();
    writer.write(2,10,"BUSCAR POR RANGO DE FECHAS");

    writer.write(4,5,"Fecha Inicial: ");
    fechaIni = writer.readDateString(4,15);

    writer.write(5,5,"Fecha Final: ");
    fechaFin = writer.readDateString(4,15);

    vector<Transaction> vec =  blockchain.findTransactionsByRangeof(fechaIni,fechaFin);

    writer.write(7,5,"Se han encontrado los siguientes resultados");

    int row = 7;
    for (Transaction transaction: vec){
        string ss = "ID Transaccion: " + std::to_string( transaction.idTransaccion );
        writer.write(++row, 10, ss);
        ss = "Nombre Emisor:" +  transaction.nombreOrigen;
        writer.write(++row, 10, ss);
        ss = "Nombre Receptor:" +  transaction.nombreDestino;
        writer.write(row, 50, ss);
        ss = "Importe: " + std::to_string( transaction.importe );
        writer.write(++row, 10, ss);
        ss = "Fecha:" +  transaction.fecha;
        writer.write(row, 50, ss);
        row++;
        if (row >25){
            writer.write(row+4,5,"Presione una tecla para continuar o [Q] para regresar a menu");
            int x = writer.getwchr();
            switch( x ) {                
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
            
            writer.write(7,5,"Se han encontrado los siguientes resultados");
            row = 7;
        }
        

    }
    if (row<=30){
        writer.write(row+4,5,"Presione una tecla para continuar ");
        writer.getwchr();
    }
}

void InsertarBloque(Blockchain & blockchain, ConsoleWriter writer){

    int row= 5;
    int ntran =0;
    int nroTran=0;
    string nombreEmisor, nombreReceptor, fechatrans;
    double importe;
    int nroRegPorBloque = 5;
    int nrotransenbloque = 0;

    vector<Transaction> transaction;
    writer.clearScreen();
    writer.write(2,10,"INSERTAR BLOQUE");

    writer.write(4,5,"Indicar el número de transacciones a ingresar: ");
    ntran = writer.readInt();
    for (int i=1; i<= ntran;i++ ){
        string ss = "ID Transaccion: " + std::to_string(i);
        writer.write(++row,5,ss);
        writer.write(++row,5,"Ingresa Nro. Transacción: ");
        nroTran = writer.readInt();
        writer.write(++row,5,"Nombre Emisor:");
        nombreEmisor = writer.readString();
        writer.write(row,50,"Nombre Receptor:");
        nombreReceptor = writer.readString();

        writer.write(++row,5,"Importe: ");
        importe = writer.readDouble();

        writer.write(row,50,"Fecha Transacción (yyyy-mm-dd): ");
        fechatrans = writer.readDateString(row, 83);
        transaction.push_back({nroTran,nombreEmisor ,nombreReceptor, importe, fechatrans});
        ++row;
        if(nrotransenbloque<nroRegPorBloque-1){            
            nrotransenbloque++;
        }
        else{
            blockchain.addBlock(transaction);
            nrotransenbloque=0;
            transaction.clear();
            row= 5;
            writer.clearScreen();
            writer.write(2,10,"INSERTAR BLOQUE");
            ss = "Indicar el número de transacciones a ingresar: " + std::to_string(ntran);
            writer.write(4,5,ss);

        }   

    }
    if (!transaction.empty()){
         blockchain.addBlock(transaction);
    }

}

void borrarBloque(Blockchain & blockchain, ConsoleWriter writer) {
    writer.clearScreen();
    writer.write(2,10,"BORRAR BLOQUE");
    writer.write(4,5,"Indicar el id del bloque a eliminar: ");
    int id_bloque = writer.readInt();
    blockchain.deleteBlock(id_bloque);
    writer.write(7,5,"Eliminado correctamente el Bloque con id: " + to_string(id_bloque));
    writer.write(9,5,"Presione cualquier tecla para salir al menu principal.");
    writer.getchr();
    return;
}

void actualizarBloque(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"ACTUALIZAR BLOQUE");
    writer.write(4,5,"Indicar el id del bloque a eliminar: ");
    int id_bloque = writer.readInt();
    writer.write(6,5,"Indicar el número de transacciones a ingresar (max 5):");
    int nro_trans = writer.readInt();
    if (nro_trans <= 0 || nro_trans > 5) {
        writer.write(8,5,"Valor incorrecto!");
        writer.write(9,5,"Presione cualquier tecla para salir al menu principal.");
        writer.getchr();
        return;
    }
    vector<Transaction> transactions;
    int row = 5;
    writer.clearScreen();
    writer.write(2,10,"ACTUALIZAR BLOQUE");
    for (int i=1; i<= nro_trans;i++ ){
        string ss = "ID Transaccion: " + std::to_string(i);
        writer.write(++row,5,ss);
        writer.write(++row,5,"Ingresa Nro. Transacción: ");
        int nroTran = writer.readInt();
        writer.write(++row,5,"Nombre Emisor:");
        string nombreEmisor = writer.readString();
        writer.write(row,50,"Nombre Receptor:");
        string nombreReceptor = writer.readString();

        writer.write(++row,5,"Importe: ");
        double importe = writer.readDouble();

        writer.write(row,50,"Fecha Transacción (yyyy-mm-dd): ");
        string fechatrans = writer.readString();
        transactions.push_back({nroTran,nombreEmisor ,nombreReceptor, importe, fechatrans});
        ++row;
    }

    blockchain.updateDataBlock(id_bloque, transactions);
    writer.clearScreen();
    writer.write(2,10,"ACTUALIZAR BLOQUE");
    writer.write(4,5,"Actualizado correctamente el Bloque con id: " + to_string(id_bloque));
    writer.write(5,5,"Presione cualquier tecla para salir al menu principal.");
    writer.getchr();
    return;
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
            writer.write(row, 50, ss);
            ss = "Importe: " + std::to_string( transaction.importe );
            writer.write(++row, 10, ss);
            ss = "Fecha:" +  transaction.fecha;
            writer.write(row, 50, ss);
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


void cargarArchivoCSV(Blockchain & blockchain, ConsoleWriter writer){
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

void buscarPorEmisor(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"OPCION - Buscar transacciones por Emisor");
    writer.write(5,10,"Ingresar el nombre exacto del emisor para buscar todas las transacciones: ");

    string nombreEmisor = writer.readString();

    int row = 4;
    string ss;
    vector<Transaction> vectorEmisor = blockchain.findTransactionsByFromName(nombreEmisor);
    if (vectorEmisor.empty()) {
        writer.write(7,10,"No existen transacciones emitidas por: " + nombreEmisor);
        writer.write(9,10,"Presione cualquier tecla para salir al menu principal.");
        writer.getchr();
        return;
    }
    writer.clearScreen();
    vector<Transaction>::iterator ite = vectorEmisor.begin();
    while (ite != vectorEmisor.end()) {
        ss = "ID Transaccion: " + to_string( (*ite).idTransaccion );
        writer.write(++row, 10, ss);      
        ss = "Nombre Emisor: " + (*ite).nombreOrigen;
        writer.write(++row, 10, ss);      
        ss = "Nombre Receptor: " + (*ite).nombreDestino;
        writer.write(++row, 10, ss);      
        ss = "Importe: " + to_string( (*ite).importe );
        writer.write(++row, 10, ss);      
        ss = "Fecha: " + (*ite).fecha;
        writer.write(++row, 10, ss);  

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

void buscarPorReceptor(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"OPCION - Buscar transacciones por Receptor");
    writer.write(5,10,"Ingresar el nombre exacto del receptor para buscar todas las transacciones: ");

    string nombreReceptor = writer.readString();

    int row = 4;
    string ss;
    vector<Transaction> vectorReceptor = blockchain.findTransactionsByToName(nombreReceptor);
    if (vectorReceptor.empty()) {
        writer.write(7,10,"No existen transacciones recibidas por: " + nombreReceptor);
        writer.write(9,10,"Presione cualquier tecla para salir al menu principal.");
        writer.getchr();
        return;
    }
    writer.clearScreen();
    vector<Transaction>::iterator ite = vectorReceptor.begin();
    while (ite != vectorReceptor.end()) {
        ss = "ID Transaccion: " + to_string( (*ite).idTransaccion );
        writer.write(++row, 10, ss);      
        ss = "Nombre Emisor: " + (*ite).nombreOrigen;
        writer.write(++row, 10, ss);      
        ss = "Nombre Receptor: " + (*ite).nombreDestino;
        writer.write(++row, 10, ss);      
        ss = "Importe: " + to_string( (*ite).importe );
        writer.write(++row, 10, ss);      
        ss = "Fecha: " + (*ite).fecha;
        writer.write(++row, 10, ss);  

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

void buscarMontoMaximo(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"Buscar Monto Máximo");
    writer.write(4,5,"La transacción con importe máximo registrado es: ");
    
    Transaction maxTransaction = blockchain.findMaxTransaction();

    int row = 6;
    writer.write(row++, 5, "ID Transaccion: " + to_string( maxTransaction.idTransaccion )); 
    writer.write(row++, 5, "Nombre Emisor: " + maxTransaction.nombreOrigen);      
    writer.write(row++, 5, "Nombre Receptor: " + maxTransaction.nombreDestino);      
    writer.write(row++, 5, "Importe: " + to_string( maxTransaction.importe ));      
    writer.write(row++, 5, "Fecha: " + maxTransaction.fecha);

    writer.write(row+2, 5, "Presione cualquier tecla para regresar al menu");

    writer.getchr();
}


void buscarMontoMinimo(Blockchain & blockchain, ConsoleWriter writer){
    writer.clearScreen();
    writer.write(2,10,"Buscar Monto Mínimo");
    writer.write(4,5,"La transacción con importe mínimo registrado es: ");
    
    Transaction minTransaction = blockchain.findMinTransaction();

    int row = 6;
    writer.write(row++, 5, "ID Transaccion: " + to_string( minTransaction.idTransaccion )); 
    writer.write(row++, 5, "Nombre Emisor: " + minTransaction.nombreOrigen);      
    writer.write(row++, 5, "Nombre Receptor: " + minTransaction.nombreDestino);      
    writer.write(row++, 5, "Importe: " + to_string( minTransaction.importe ));      
    writer.write(row++, 5, "Fecha: " + minTransaction.fecha);

    writer.write(row+2, 5, "Presione cualquier tecla para regresar al menu");

    writer.getchr();
}