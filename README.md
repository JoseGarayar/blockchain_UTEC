# PROYECTO 1 - BLOCKCHAIN INDEXING

## 1. Introducción

Este proyecto del curso de estructura de datos - maestría UTEC 2023 consiste en desarrollar una aplicación transaccional de almacenamiento seguro de datos, en donde los datos serán almacenados en una cadena de bloques codificados (Blockchains en un solo host), y permitirá búsquedas eficientes, los registros serán indexados con diferentes estructuras de datos desarrollados por los miembros del grupo.

El grupo esta conformado por los alumnos:
- Jose Garayar
- Roberth Ramos
- Juan José Granados
- Carlos Villanueva

## 2. Descripción del caso de estudio planteado por el grupo

El presente informe describe el proyecto de desarrollo de un blockchain con indexación eficiente diseñado específicamente para almacenar y gestionar información de transacciones financieras. El blockchain actuará como un registro seguro de datos que contendrá detalles clave de las transacciones, como el emisor, el receptor, el monto y la fecha. Además, se implementarán estructuras de datos avanzadas para permitir una búsqueda rápida y eficiente de la información almacenada en el blockchain.

## 3. Importancia del Blockchain en el dominio de datos elegido 

El uso de blockchain en el ámbito financiero ha ganado popularidad en los últimos años debido a su capacidad para garantizar la transparencia, seguridad y confiabilidad de las transacciones. Sin embargo, a medida que el volumen de transacciones financieras continúa aumentando, surge la necesidad de optimizar la forma en que se almacena y recupera la información en un blockchain. Este proyecto tiene como objetivo abordar esta necesidad al desarrollar un blockchain con indexación eficiente para transacciones financieras.

## 4. Explicación de la estructura de datos del Blockchain y la estrategia para asegurar la integridad de su contenido. Además, indicar cómo se implementó el proof of work. 

### - Explicación de las estructuras de datos usadas en el Blockchain

#### **Circular Double List**

En un blockchain, una estructura de datos comúnmente utilizada es la lista circular doblemente enlazada. Esta estructura se utiliza para mantener un registro de transacciones en un orden específico y permitir un acceso eficiente a los bloques de datos.

La lista circular doblemente enlazada consta de nodos, donde cada nodo contiene dos punteros: uno hacia el nodo anterior y otro hacia el siguiente nodo en la lista. El primer nodo se enlaza con el último nodo de la lista, creando así un ciclo continuo.

En el contexto de un blockchain, cada bloque de transacciones se puede representar como un nodo en la lista circular doblemente enlazada. Cada nodo contendría la información del bloque, como el hash del bloque anterior, el hash del bloque actual, la información de las transacciones.

Aquí hay una representación visual de la estructura de la lista circular doblemente enlazada en un blockchain:

   ![Blockchain](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/effbf741-d878-4261-8512-07dd982963b8)

La informacion de la transaccion estara constituido por el ID de la transaccion, Emisor, Receptor, Importe y Fecha. Se pueden realizar distintas transacciones y almacenarlas en un bloque utilizando la clase desarrollado "Block"; para luego ser estructurado en lista circular doblemente enlazada a travez del metodo "addBlock" de la clase Blockchain creada.  .

![INTRODEDATOS](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/19fd0bdc-ecd5-42e5-845d-8785587ee00b)

La Clase block como se observa no solo contiene la transaccion efectuada, tambien lo que es el indice de la lista circular doblemente enlazada en la que se va a ubicar, el previousHash, el nonce y el hash . 

``` js
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
};

```

Cada bloque creado sera introducido en el blockchain (lista circular doblemente enlazada) mediante un push_back aplicado en el metodo "addBlock" de la clase "Blockchain"

``` js
class Blockchain {
private:
    
    CircularDoubleList<Block*> blockchain;

public:
    typedef CircularDoubleListIterator<Block*> iterator;

    Blockchain() {}

    void addBlock(vector<Transaction>& data) {
        int index = blockchain.size();
        const string& previousHash = index != 0 ? blockchain.back()->getHash() : defaultHash();
        Block* newBlock = new Block(index, data, previousHash);
        blockchain.push_back(newBlock);        
        
    }
```

La identidad propia del bloque hijo cambia si la identidad del padre cambia.Es decir: 
  *	Si por alguna razón el contenido del bloque padre se modifica, el código hash del padre también cambia. 
  *	El cambio de hash del padre requiere una alteración en el puntero "Prev" del hijo. 
  *	Esto, a su vez, hace que el hash del hijo mute, lo que requiere un cambio en el puntero del nieto, que a su vez altera al nieto y así sucesivamente. 

Para este escenario se implemento el metodo "cascadeEffect()" en la clase "Blockchain", que genera otros actualizados hashcode y previous hash del bloque a partir del padre bloque actualizado (o borrado) 

``` js
    void cascadeEffect() {
        CircularDoubleList<Block*>::iterator ite = blockchain.begin();
        CircularDoubleList<Block*>::iterator ite_prev = blockchain.begin();
        int i = 0;
        for(; ite != blockchain.end(); ++ite){
            if (i == 0) {
                (*ite)->update_block(i, (*ite)->getData(), defaultHash());
                ite_prev = ite;
            } else {
                (*ite)->update_block(i, (*ite)->getData(), (*ite_prev)->getHash());
                ++ite_prev;
            }
            i++;
        }
    }
```
Se mostraran el efecto cascada en la siguientes imagenes

**Blockchain Inicial**

![blockhchain actual](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/432819bf-e825-4d24-8bf9-83027426d8dd)


**Blockchain Con Transaccion Modificada**

![blockhchain modificado](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/c890277e-b052-443d-8a05-6273baaa2ff6)


**Blockchain Con Bloque Eliminado**

![blockhchain eliminado](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/828afd82-1956-4f6c-be28-6317eb0dfd3f)

### - Prueba de trabajo

En un blockchain, la técnica de Prueba de Trabajo (Proof of Work, PoW) se utiliza como mecanismo de consenso para validar transacciones y asegurar la integridad de la cadena de bloques. Hay varias implementaciones de Prueba de Trabajo, pero las más comunes son las siguientes:

| Opcion | Descripcion |
| ------ | ----------- |
| Hashcash |  Hashcash fue la primera implementación de Prueba de Trabajo utilizada en el protocolo de correo electrónico para prevenir el spam. En Hashcash, se requiere que los participantes encuentren un nonce (número arbitrario utilizado solo una vez) que, al ser aplicado a una función hash criptográfica, genere un valor hash que cumpla con ciertos requisitos, como tener un cierto número de ceros iniciales. La dificultad se puede ajustar mediante la variación de la cantidad de ceros requeridos.|
| Bitcoin PoW | Bitcoin utiliza una variante de la Prueba de Trabajo basada en Hashcash. En este caso, los mineros deben encontrar un nonce que, junto con otros datos, genere un hash que cumpla con una dificultad específica. La dificultad se ajusta periódicamente para mantener el tiempo promedio de bloqueo en aproximadamente 10 minutos. |
| Ethash (Ethereum) | Ethereum utiliza el algoritmo Ethash como su Prueba de Trabajo. En Ethash, en lugar de solo buscar un nonce, se requiere que los mineros realicen una gran cantidad de cálculos de acceso a memoria, lo que dificulta la implementación de hardware especializado para minar de manera eficiente. |
| Equihash (Zcash) | Equihash es otro algoritmo de Prueba de Trabajo utilizado en la criptomoneda Zcash. Se basa en el problema de los "circuitos generalizados de satisfacción de la condición" (generalized birthday problem) y requiere una gran cantidad de memoria, lo que también dificulta la implementación de hardware especializado.|

Para el proyecto se escogió la técnica de Hashcash donde el número de ceros iniciales es de solo 4 ceros, ya que se busca un equilibrio entre seguridad y eficiencia.

Ya que cada bloque es identificable por un código hash, generado mediante un algoritmo de hash criptográfico a partir de toda la información que contiene el bloque. En nuestra clase "Block" se generara a traves del metodo "mineBlock()" 

``` js
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
```
El metodo "mineBlock()"  que en base a la tecnica Hacash mina un hash_code con 4 ceros iniciales utilizando una funcion hash, dicha funcion para mantener las propiedades del hash (indexación eficiente en el rendimiento de las búsquedas, libre de colisiones, estable y segura) utilizamos una librería estándar de criptografía como  OpenSSL.

``` js
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
```

## 5. Explicación de cada una de las estructuras de datos utilizada en su aplicación de acuerdo a los criterios de búsqueda.

Dado que se requiere una aplicación transaccional que permita a un usuario registrar transacciones bancarias de manera segura en el Blockchain, para luego aplicar búsquedas eficientes usando diversas estructuras de datos como mecanismos de indexación para diferentes criterios de búsqueda. Utilizaremos para nuestra aplicacion las estructuras Hash **table**, **Arbol binario BST** , y **Heap**

![estructuras de indexacion (2)](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/3d6382f3-6145-4a5a-828b-f524738d80c0)

Dado los siguientes criterios de búsqueda, para indexar los bloques usaremos la estructura de datos más apropiada de acuerdo al tipo de filtrado requerido:
1.	Igual a X 
vector<Record>  search(TK key)
2.	Entre X y Y 
vector<Record> range_search(TK begin, TK end)
3.	Inicia con 
vector<Record> start_with(string prefix)
4.	Máximo valor de 
Record max_value( )
5.	Mínimo valor de
Record min_value( )

#### **Hash Table**
  
**Igual a X**
**vector<Record>  search(TK key)**
En el blockchain, utilizamos un hash table como estructura de indexación para mejorar la eficiencia de la búsqueda y recuperación de información en la cadena de bloques. Un hash table es una estructura de datos que permite el acceso rápido a los datos almacenados asociándolos con claves únicas.

La razon por la que se utiliza una tabla hash en nuestro blockchain:

Búsqueda eficiente: Conforme el blockchain crece en tamaño, buscar un bloque específico o una transacción en la cadena lineal de bloques puede volverse ineficiente . Utilizando una tabla hash, se pueden generar claves únicas basadas en ciertos atributos del bloque o la transacción, como su identificador o su hash. Estas claves permiten una búsqueda directa y rápida en la tabla hash, evitando la necesidad de recorrer toda la cadena de bloques insertadas en la lista doblemente enlazadas.

Indexación de transacciones: En el caso de blockchains que almacenan transacciones, una tabla hash puede utilizarse para indexar y acceder rápidamente a transacciones específicas.

#### **BST (Binary Search Tree)**
**Entre X y Y**
**vector<Record> range_search(TK begin, TK end)**
  
Cuando se necesita buscar un rango de valores en una estructura de datos, como en el caso de buscar el monto de transaccion realizado en un intervalo específico, el BST se destaca debido a que mantienen sus elementos ordenados en función en este caso del importe. Esto permite realizar búsquedas eficientes, ya que se puede explorar el árbol de forma ordenada y descartar ramas completas según el rango especificado. Al comparar un monto con otro, se puede determinar si el rango de búsqueda se encuentra en el subárbol izquierdo, el subárbol derecho . Esto permite reducir el espacio de búsqueda en cada paso y, en promedio, acelerar la búsqueda. Para este proceso se tiene una complejidad de O(lgn)

   
#### **Heap**
**Máximo valor de**
**Record max_value( )**
**Mínimo valor de**
**Record min_value( )**
  
Para realizar búsqueda del máximo y mínimo importe transferido se utilizó la estructura de datos `Heap`, `MaxHeap` y `MinHeap` para obtener el máximo y mínimo importe respectivamente con una complejidad de O(1).

## 6. Análisis de la complejidad en notación Big O de los métodos del Blockchain.

Falta completar
- Principalmente de los métodos de insertar y buscar
- Realizar una tabla comparativa de Blockchain con índices vs sin índices.

 Se muestra una tabla comparativa de analisis de complejidad de los metodos del Blockchain con indices vs sin indices
  
| Método del Blockchain | Sin indice O( )|Con indice O( )|
| ----------------------| --------------| --------------|
|addBlock               |  O(1)         | O(lgn)        |
|deleteBlock            |  O(n)         | O(n)          | 
|updateDataBlock        |  O(n)         | O(n)     -    |    
|cascadeEffect          |  O(n)         | O(n)          |     
 
 Como se observa no existe una diferencia marcable entre el blockchain con indices y sin indice y esto es debido al metodo **"cascadeEffect"** el cual sera llamado cada vez que se hace una actualizacion de un bloque o un delete debido a que se requiere generar nuevos hash code y prev hash de los bloques. La razon que se tiene para indexar con estructuras  radica al momento de realizar el proceso de busqueda, utilizando el mejor atributo entre el Hash table, BST, Heap (Max, Min). 
En la siguiente tabla se muestra la complejidad O ( ) para los siguientes metodos de busqueda
 
| Método del Blockchain             |  O( )         |
| ----------------------------------| --------------|
|findTransactionsByFromName         |  O(k)         | 
|findTransactionsByToName           |  O(k)         | 
|findTransactionsByFromNameBeginWith|  O(lgn)       | 
|findTransactionsByRangeof          |  O(lgn)       |    
|findMaxTransaction                 |  O(1)         |       
|findMinTransaction                 |  O(1)         |      
   
   
## 7. Conclusiones

La implementación de un blockchain con indexación eficiente para transacciones financieras tiene el potencial de mejorar significativamente la forma en que se almacena y se busca información en este contexto. Al estructurar los datos y utilizar algoritmos de indexación optimizados, se espera lograr una mayor eficiencia en la recuperación de información, lo que puede beneficiar a diversos actores en el sector financiero. Sin embargo, es importante destacar que el éxito del proyecto dependerá de la implementación adecuada de las técnicas de seguridad y la selección correcta de los algoritmos de indexación para garantizar la integridad y la confiabilidad de los datos almacenados en el blockchain.

## 8. Referencias bibliográficas 

Falta completar

## 9. Anexar al informe la lista de actividades concluidas por cada integrante del grupo

Jose Garayar

- Investigar libreria OpenSSL y funcion hash de encriptacion SHA-256 para implementar funcion de cálculo de hash para bloques del blockchain.
- Investigar y aplicar concepto de prueba de trabajo.
- Implementar función de efecto cascada.
- Implementar función eliminar bloque y actualizar data del bloque para menú del blockchain.
- Implementar estructura de datos "Hash Table".
- Usar estructura de datos "Hash Table" para indexación de criterio de búsqueda "Igual a X", esto se actualiza al agregar, actualizar o eliminar bloque.
- Crear estructura de informe final en el archivo README del proyecto
- Crear tareas para cada miembro del grupo en [Board de Github Project](https://github.com/users/JoseGarayar/projects/1/views/1?layout=board).
![github_project_board](https://github.com/JoseGarayar/blockchain_UTEC/assets/53947785/398348b6-91e1-4aab-b1e7-d9560d224b9d)

Roberth Ramos

- Implementar estructura de datos "Circular Double List".
- Usar estructura de datos "Circular Double List" para crear clase Blockchain con función de agregar bloque.
- Implementar estructura de datos "BST".
- Usar estructura de datos "BST" para indexación de criterios de búsqueda "Entre X y Y" e "Inicia con", esto se actualiza al agregar, actualizar o eliminar bloque.
- Agregar información de las estructuras de datos al informe.
- Elaborar presentación PowerPoint del proyecto.
- Crear aplicación de menú por consola.

Juan José Granados

- Implementar estructura de datos "Heap".
- Usar estructura de datos "Heap" para indexación de criterios de búsqueda "Máximo valor" y "Mínimo valor", esto se actualiza al agregar, actualizar o eliminar bloque.
- Implementar método para eliminar un elemento del Heap.
- Implementar función para carga de datos desde archivo csv.
- Generar archivo csv con data de transacciones financieras.
- [Board de Github Project](https://github.com/users/JoseGarayar/projects/1/views/1?layout=board)


Carlos Villanueva

- Implementar estructura de datos "Hash Table".
- Usar estructura de datos "Hash Table" para indexación de criterio de búsqueda "Igual a X", esto se actualiza al agregar, actualizar o eliminar bloque.
- Agregar información de las estructuras de datos al informe.
- Elaborar presentación PowerPoint del proyecto.
- Elaboracion de informe final en el archivo README del proyecto
