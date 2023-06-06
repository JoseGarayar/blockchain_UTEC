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

La Clase block como se observa no solo contiene la transaccion efectuada, tambien lo que es el indice de la lista circular doblemente enlazada en la que se va a ubicar y el previousHash

![Claseblock](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/d6bed802-4665-492e-9a39-8e11b592f91b)


Cada bloque creado sera introducido en el blockchain (lista circular doblemente enlazada) mediante un push_back aplicado en el metodo "addBlock" de la clase "Blockchain"


![clase blockchain](https://github.com/JoseGarayar/blockchain_UTEC/assets/134245641/c57cdfb7-4f00-4ddb-aba5-1bbdbebaa629)


### - Prueba de trabajo

En un blockchain, la técnica de Prueba de Trabajo (Proof of Work, PoW) se utiliza como mecanismo de consenso para validar transacciones y asegurar la integridad de la cadena de bloques. Hay varias implementaciones de Prueba de Trabajo, pero las más comunes son las siguientes:

1. Hashcash: Hashcash fue la primera implementación de Prueba de Trabajo utilizada en el protocolo de correo electrónico para prevenir el spam. En Hashcash, se requiere que los participantes encuentren un nonce (número arbitrario utilizado solo una vez) que, al ser aplicado a una función hash criptográfica, genere un valor hash que cumpla con ciertos requisitos, como tener un cierto número de ceros iniciales. La dificultad se puede ajustar mediante la variación de la cantidad de ceros requeridos.

2. Bitcoin PoW: Bitcoin utiliza una variante de la Prueba de Trabajo basada en Hashcash. En este caso, los mineros deben encontrar un nonce que, junto con otros datos, genere un hash que cumpla con una dificultad específica. La dificultad se ajusta periódicamente para mantener el tiempo promedio de bloqueo en aproximadamente 10 minutos.

3. Ethash (Ethereum): Ethereum utiliza el algoritmo Ethash como su Prueba de Trabajo. En Ethash, en lugar de solo buscar un nonce, se requiere que los mineros realicen una gran cantidad de cálculos de acceso a memoria, lo que dificulta la implementación de hardware especializado para minar de manera eficiente.

4. Equihash (Zcash): Equihash es otro algoritmo de Prueba de Trabajo utilizado en la criptomoneda Zcash. Se basa en el problema de los "circuitos generalizados de satisfacción de la condición" (generalized birthday problem) y requiere una gran cantidad de memoria, lo que también dificulta la implementación de hardware especializado.

Para el proyecto se escogió la técnica de Hashcash donde el número de ceros iniciales es de solo 4 ceros, ya que se busca un equilibrio entre seguridad y eficiencia.

## 5. Explicación de cada una de las estructuras de datos utilizada en su aplicación de acuerdo a los criterios de búsqueda.

Falta completar (Use diagramas para una mejor claridad)

#### **Chainhash**

Falta completar (Indicar para que criterios de busqueda se utiliza)

#### **BST (Binary Search Tree)**

Falta completar (Indicar para que criterios de busqueda se utiliza)

#### **Heap**

Para realizar búsqueda del máximo y mínimo importe transferido se utilizó la estructura de datos `Heap`, `MaxHeap` y `MinHeap` para obtener el máximo y mínimo importe respectivamente con una complejidad de O(1).

## 6. Análisis de la complejidad en notación Big O de los métodos del Blockchain.

Falta completar
- Principalmente de los métodos de insertar y buscar
- Realizar una tabla comparativa de Blockchain con índices vs sin índices.

## 7. Conclusiones

La implementación de un blockchain con indexación eficiente para transacciones financieras tiene el potencial de mejorar significativamente la forma en que se almacena y se busca información en este contexto. Al estructurar los datos y utilizar algoritmos de indexación optimizados, se espera lograr una mayor eficiencia en la recuperación de información, lo que puede beneficiar a diversos actores en el sector financiero. Sin embargo, es importante destacar que el éxito del proyecto dependerá de la implementación adecuada de las técnicas de seguridad y la selección correcta de los algoritmos de indexación para garantizar la integridad y la confiabilidad de los datos almacenados en el blockchain.

## 8. Referencias bibliográficas 

Falta completar

## 9. Anexar al informe la lista de actividades concluidas por cada integrante del grupo

Jose Garayar:

- Investigar libreria OpenSSL y funcion hash de encriptacion SHA-256 para implementar funcion de cálculo de hash para bloques del blockchain.
- Investigar y aplicar concepto de prueba de trabajo.
- Implementar función de efecto cascada.
- Implementar función eliminar bloque y actualizar data del bloque para menú del blockchain.
- Crear estructura de informe final en el archivo README del proyecto
- Crear tareas para cada miembro del grupo en Github Project Boards. Enlace: https://github.com/users/JoseGarayar/projects/1/views/1?layout=board
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

- Implementar estructura de datos "Chain Hash".
- Usar estructura de datos "Chain Hash" para indexación de criterio de búsqueda "Igual a X", esto se actualiza al agregar, actualizar o eliminar bloque.
- Agregar información de las estructuras de datos al informe.
- Elaborar presentación PowerPoint del proyecto.
