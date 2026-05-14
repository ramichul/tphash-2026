# TP: Diccionario
## Información del estudiante

* **Nombre y Apellido**: Ramiro Carrattini
* **Padrón**: 113212
* **Mail**: ramirocarrattini@gmail.com / rcarrattini@fi.uba.ar

---

# Índice
- [TP: Diccionario](#tp-diccionario)
  - [Información del estudiante](#información-del-estudiante)
- [Índice](#índice)
  - [1. Instrucciones](#1-instrucciones)
    - [1.1. Compilar el proyecto](#11-compilar-el-proyecto)
    - [1.2. Ejecutar las pruebas](#12-ejecutar-las-pruebas)
    - [1.3. Ejecutar el programa con Valgrind](#13-ejecutar-el-programa-con-valgrind)
  - [2. Funcionamiento](#2-funcionamiento)
    - [Estructuras](#estructuras)
      - [Diccionario](#diccionario)
      - [Par](#par)
    - [Primitivas y funcionamiento interno](#primitivas-y-funcionamiento-interno)
      - [Creación](#creación)
      - [Inserción](#inserción)
      - [Eliminación](#eliminación)
      - [Busqueda](#busqueda)
      - [Cantidad](#cantidad)
      - [Iteración](#iteración)
      - [Destrucción](#destrucción)
    - [Complejidades temporales](#complejidades-temporales)
    - [Flujo del programa de prueba implementado](#flujo-del-programa-de-prueba-implementado)
  - [3. Respuestas a las preguntas teóricas](#3-respuestas-a-las-preguntas-teóricas)
      - [¿Qué es un diccionario? Explicar 3 formas diferentes de implementar un diccionario.](#qué-es-un-diccionario-explicar-3-formas-diferentes-de-implementar-un-diccionario)
      - [¿Qué es una función de Hash? ¿Qué características debe tener para nuestro problema en particular?](#qué-es-una-función-de-hash-qué-características-debe-tener-para-nuestro-problema-en-particular)
      - [¿Qué es una tabla de Hash? Explicar los diferentes métodos de resolución de colisiones vistos.](#qué-es-una-tabla-de-hash-explicar-los-diferentes-métodos-de-resolución-de-colisiones-vistos)
      - [Explique por qué es importante el tamaño de la tabla (tanto para tablas abiertas como cerradas). Dado que en una tabla abierta se pueden encadenar colisiones sin importar el tamaño de la tabla, ¿Realmente importa el tamaño?](#explique-por-qué-es-importante-el-tamaño-de-la-tabla-tanto-para-tablas-abiertas-como-cerradas-dado-que-en-una-tabla-abierta-se-pueden-encadenar-colisiones-sin-importar-el-tamaño-de-la-tabla-realmente-importa-el-tamaño)
  - [4. Aclaraciones sobre la implementación y el *TDA* auxiliario](#4-aclaraciones-sobre-la-implementación-y-el-tda-auxiliario)

## 1. Instrucciones
### 1.1. Compilar el proyecto
```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 main.c src/*.c -o diccionario_pokemon
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 src/*.c pruebas/pruebas_alumno.c -o pruebas_alumno
```

### 1.2. Ejecutar las pruebas
```bash
./diccionario [archivo] buscar nombre/tipo [parámetro a buscar]
./pruebas_alumno
```

### 1.3. Ejecutar el programa con Valgrind
```bash
valgrind ./diccionario [archivo] buscar nombre/tipo [parámetro a buscar]
valgrind ./pruebas_alumno
```

&nbsp;

## 2. Funcionamiento
### Estructuras
#### Diccionario
Es la estructura principal del proyecto, basada en una Tabla de Hash abierta. Utiliza un vector de varios *TDA* Lista (cuyo funcionamiento está detallado en [este directorio](https://github.com/ramichul/tplista-2026)) como contenedores para los diferentes pares. Cuenta con una capacidad específica o cantidad de contenedores que se va redimensionando a medida que el usuario inserta elementos en el diccionario. Este proceso es explicado en detalle más adelante.
#### Par
Es el contenedor de datos que rellena las diferentes listas de la tabla. Está compuesto por una clave, la cual tiene asociada un valor.

Se adjunta una visualización de las diferentes estructuras en memoria:

![Diagrama de las estructuras en memoria](https://i.imgur.com/s95YXye.png)
&nbsp;
### Primitivas y funcionamiento interno
#### Creación
**`diccionario_t *diccionario_crear(size_t capacidad_inicial)`**: Crea un diccionario vacío con una `capacidad_inicial` dada. La capacidad nunca puede ser menor a 3. Devuelve el diccionario o `NULL` en caso de error.

Internamente, esta primitiva reserva memoria tanto para el diccionario como sus contenedores. Se crean las listas una por una y se va rellenando el vector de la estructura con ellas.


#### Inserción
**`diccionario_t *diccionario_insertar(diccionario_t *d, const char *clave, void *valor, void **valor_anterior)`**: Inserta un `valor` asociado a una `clave`. Si `valor_anterior` es un puntero válido, se almacena el valor previamente almacenado para la clave dada (o `NULL` en caso de que no existiera la clave). Devuelve el diccionario o `NULL` en caso de error.


#### Eliminación
**`void *diccionario_eliminar(diccionario_t *d, const char *clave)`**: Elimina una `clave` del diccionario. Devuelve el valor asociado a la clave eliminada o `NULL` en caso de error.

Se obtiene el Hash a partir de la clave y se ejecuta `lista_buscar()` sobre el contenedor indicado para obtener su posición dentro del mismo. Se llama a `lista_eliminar_posicion()` con el índice obtenido. Se extraen los datos del par, guardando su valor en un puntero auxiliar antes de liberar la memoria que ocupaba. Se devuelve este puntero auxiliar.

#### Busqueda
**`void *diccionario_obtener(diccionario_t *d, const char *clave)`**: Devuelve el valor asociado con una `clave` en el diccionario o `NULL` en caso de error.

Se obtiene el Hash a partir de la clave y se ejecuta `lista_buscar()` sobre el contenedor indicado, comparando los nombres de las claves con `strcmp()` uno por uno hasta encontrar la clave buscada. Si la clave estaba presente en el diccionario al momento de buscar, se extraen los datos del par correspondiente y se devuelven.

**`bool diccionario_existe(diccionario_t *d, const char *clave)`**: Devuelve `true` si la `clave` existe dentro del diccionario.

Funciona idénticamente a `diccionario_obtener()`, solo que replica el booleano que devuelve `lista_buscar()` en vez de extraer datos para cubrir el caso donde se está buscando un valor nulo.


#### Cantidad
**`size_t diccionario_cantidad(diccionario_t *d)`**: Devuelve la cantidad de claves almacenadas en el diccionario.

Internamente, se accede al campo `d->cantidad_elementos` y se lo devuelve al usuario.


#### Iteración
**`size_t diccionario_con_cada_elemento(diccionario_t *d, bool (*f)(struct diccionario_par *, void *), void *extra)`**: Invoca la función `f` con cada par almacenado en el diccionario. Si la función `f` devuelve `false`, finaliza la iteración. Devuelve la cantidad de elementos iterados.

Se crea un iterador externo de Lista para cada contenedor del diccionario y se le va aplicando la función `f` a cada par dentro de él.


#### Destrucción
**`void diccionario_destruir_todo(diccionario_t *d, void (*destructor)(void *))`**: Destruye el diccionario y aplica la función `destructor` a cada valor almacenado.

**`void diccionario_destruir(diccionario_t *d)`**: Destruye el diccionario.
&nbsp;

### Complejidades temporales
Se toma a $n$ como la cantidad de pares y $m$ como la lóngitud de las claves.

|      Función      |Complejidad|                 Justificación                  |
|:-----------------:|:---------:|:----------------------------------------------:|
|      `diccionario_crear()`       |  $O(n)$   |Además del diccionario, se debe reservar memoria para un total de $n$ contenedores.|
|      `diccionario_insertar()`       |  $O(n\cdot m)$   |Al rehashear, se llama a la función `rehashear_elemento()` $n$ veces, que a su vez llama a `obtener_hash()` ($O(m)$) una vez.|
|      `diccionario_eliminar()`       |  $O(n\cdot m)$ |Al buscar en la Lista, se utiliza la función $O(m)$, `strcmp()`, una vez para cada una de las $n$ claves.|
|      `diccionario_obtener()`       |  $O(n\cdot m)$ |Al buscar en la Lista, se utiliza la función $O(m)$, `strcmp()`, una vez para cada una de las $n$ claves.|
|      `diccionario_existe()`       |  $O(n\cdot m)$ |Al buscar en la Lista, se utiliza la función $O(m)$, `strcmp()`, una vez para cada una de las $n$ claves.|
|      `diccionario_cantidad()`       |  $O(1)$ |Simplemente se devuelve el valor `cantidad_elementos`.|
|      `diccionario_con_cada_elemento()`       |$O(n\cdot f(n))$|Se ejecutan varias primitivas del iterador externo de Lista (todas $O(1)$) $n$ veces. Se toma a $f(n)$ como la función que acota la complejidad temporal de `f`.|
|      `diccionario_destruir()`       |  $O(n²)$ |La función $O(n)$, `lista_destruir()`, se llama una vez por cada uno de los $n$ contenedores.|
|      `diccionario_destruir_todo()`       |  $O(n²\cdot f(n))$ |Además de `lista_destruir()`, se llama a `destructor()` $n$ veces. Se toma a $f(n)$ como la función que acota la complejidad temporal de esta última.|
|      Buscar un Pokémon por nombre       |  $O(n\cdot m)$ |Además de `imprimir_pokemon()` que es $O(1)$, Se utiliza `diccionario_obtener()` para realizar esta tarea.|
|      Buscar Pokémon por tipo       |  $O(n)$ |Además de `imprimir_pokemon()`, se utiliza `diccionario_con_cada_elemento()` con la función $O(1)$ `mostrar_pokemon_por_tipo()` para esta tarea.|


### Flujo del programa de prueba implementado
Se implementó un programa de busqueda de Pokémon con ayuda de la estructura de Pokédex (detallada en [este directorio](https://github.com/ramichul/tp1-2026)) para comprobar el buen funcionamiento y las capacidades del diccionario. Su funcionamiento es el siguiente (dando por sentado que el programa se abortará cuando haya sucedido un error):
1. Antes de buscar, se parsean los argumentos. En este proceso se detectan comandos inválidos, cantidades imposibles de argumentos, parámetros inválidos para la busqueda por tipo, etc.
2. Una vez validados los argumentos, se crea la Pokédex y se extraen los datos desde el archivo pasado por línea de comando. Si al finalizar la Pokédex está vacía, se le avisará de esto al usuario y no se seguirán procesando los datos.
3. Se crea el diccionario. Se insertan los Pokémon en él uno por uno utilizando `tp1_con_cada_pokemon()`. La estructura de Pokédex garantiza que no hayan Pokémon repetidos por nombre, dandonos la libertad de utilizar su nombre como clave.
4. Se identifica la instrucción entre busqueda por nombre o por tipo y se manda a ejecutar la función correspondiente.
5. Si la busqueda es por nombre, se utiliza `diccionario_obtener()` para buscar el Pokémon dentro del diccionario. Una vez obtenido, se imprimen sus datos por pantalla. Si el Pokémon no fue encontrado, se le avisa de esto al usuario.
6. Si la busqueda es por tipo, se utiliza `diccionario_con_cada_elemento()` para identificar los Pokémon uno por uno, y luego se imprimen sus datos por pantalla si son del tipo buscado.
7. Se libera la memoria utilizada y se termina la ejecución del programa.

&nbsp;

## 3. Respuestas a las preguntas teóricas
#### ¿Qué es un diccionario? Explicar 3 formas diferentes de implementar un diccionario.
Un diccionario es una estructura que almacena pares clave-valor. Gracias a esta característica, los valores almacenados se pueden acceder rápidamente buscando por su clave asociada en vez de ir elemento por elemento.
Existen varias formas de implementar un diccionario:
- Utilizando una Tabla de Hash: Utiliza una función de Hash, que recibe una clave y la transforma en un índice. Esta puede ser tanto abierta (de direccionamiento cerrado) como cerrada (de direccionamiento abierto):
  - Tabla de Hash abierta: Utiliza una estructura auxiliar como "contenedor" para cada índice de la tabla. Se considera de "direccionamiento cerrado" porque se garantiza que el elemento se insertará en la posición indicada por la función de Hash al poderse almacenar varios elementos por posición.
  - Tabla de Hash cerrada: Almacena los elementos directamente dentro de la tabla misma. El direccionamiento en este caso es "abierto" ya que no necesariamente siempre coinciden la posición final y la indicada por la función de Hash. Como no se puede insertar un elemento en una posición ya ocupada al colisionar, se debe encontrar una alternativa.

- Mediante una lista enlazada: Se pueden almacenar los pares directamente dentro de una lista enlazada, y buscar linealmente cada vez que se necesite operar con o acceder a una clave.

- Mediante un ABB: Se puede utilizar un ABB para almacenar los pares, ordenando las claves para optimizar la búsqueda.

Se pueden ver diagramas ilustrando ambas versiones de la primera forma en [este apartado del informe](#qué-es-una-tabla-de-hash-explicar-los-diferentes-métodos-de-resolución-de-colisiones-vistos). Se considera redundante ilustrar la segunda forma ya que es funcionalmente idéntico a un contenedor individual de una tabla de Hash abierta utilizando Listas.

Se adjunta un diagrama mostrando un ejemplo de un diccionario implementado con un ABB, en donde las claves son enteros ordenados por mágnitud:

![Diagrama de diccionario implementado con ABB](https://i.imgur.com/1PLhVrW.png)

&nbsp;
#### ¿Qué es una función de Hash? ¿Qué características debe tener para nuestro problema en particular?
Una función de Hash es aquella que dada una clave, la convierte en un número asociado. Para que se pueda utilizar con las estructuras implementadas, se deben considerar varias cosas:
1. Es necesario que la función devuelva un valor **fijo** para cada clave, asegurando que su comportamiento sea predecible.
2. Como el valor que devuelve la función es interpretado como una posición en la tabla de Hash, este debe ser acotado para que no se accedan a indíces inválidos.
3. Se debe diseñar la función de manera que sea de alta varianza. Es decir, los Hashes resultantes deben estar bien dispersos sobre los valores de salida posibles. Esto resulta en menos colisiones, y por ende optimiza muchos aspectos del funcionamiento de la estructura.
4. Como la función se estará ejecutando constantemente, esta debe ser lo más rápida y eficiente posible.
&nbsp;
#### ¿Qué es una tabla de Hash? Explicar los diferentes métodos de resolución de colisiones vistos.
Una tabla de Hash es un *Tipo de Dato Abstracto (TDA)* que permite almacenar distintos elementos dentro de ella. Su principal característica es que permite hallar un valor rápidamente utilizando la función de Hash, que recibe una clave y la transforma en un índice. Los elementos (para un Hash cerrado) o contenedores (Hash abierto) de la tabla siguen un orden especificado, y el lugar de cada uno es numerado con un índice. 
Es posible que dos elementos diferentes resulten tener el mismo Hash. Este evento se denomina colisión, y se puede afrontar de diferentes maneras según como esté implementado el *TDA*:
- *Chaining* o Encadenamiento: Este método es exclusivo al Hash abierto, y es el que utiliza el *TDA* implementado. Se calcula el índice mediante la función de hash y el elemento se inserta en el contenedor ubicado en dicha posición. Cada índice de la tabla almacena todos los elementos cuyo hash produce ese mismo índice. Un ejemplo visual utilizando una lista enlazada como contenedor se vería de la siguiente forma:
![Ejemplo de chaining](https://i.imgur.com/HJavszM.png)

- *Probing*: Se utiliza en el Hash cerrado. En el evento de una colisión, se sigue recorriendo la tabla hasta encontrar el próximo espacio libre. Una vez encontrado, se inserta el par en esa posición. Hay tres formas diferentes de realizarlo:
    - *Probing* lineal: Busca el siguiente espacio libre recorriendo las posiciones una por una.
    - *Probing* cuadrático: En vez de usar un paso constante como lo hace el *Probing* lineal, la busqueda se realiza de a saltos cuadráticos. Cada vez que se encuentra una posición ocupada, el salto se duplíca. Si, por ejemplo, el Hash recibido es $0$, las posiciones comprobadas serían $0, 1, 3, 7, \dots$ hasta encontrar un lugar libre.

- Hash doble: Se aplíca una función de Hash diferente a la clave cuando hay una colisión. Si esta también falla, se utilizará otra función.

Se puede visualizar como los distintos métodos manejan las colisiones en los siguientes diagramas: 

![Ejemplos de probing](https://i.imgur.com/s3vwpQS.png)
&nbsp;
#### Explique por qué es importante el tamaño de la tabla (tanto para tablas abiertas como cerradas). Dado que en una tabla abierta se pueden encadenar colisiones sin importar el tamaño de la tabla, ¿Realmente importa el tamaño?
El tamaño de la tabla es importante porque influye directamente en la cantidad de colisiones, tanto en el Hash abierto como en el cerrado.

Más allá de que el Hash abierto teorícamente tenga capacidad infinita sin importar el tamaño de la tabla, su rendimiento será mucho menor mientras más colisiones haya porque se le darán más objetos para recorrer por contenedor. Eventualmente, muchas de las operaciones (que están pensadas para promediar un tiempo de ejecución constante) tienden a ser $O(n)$ y deja de ser eficiente el uso de la tabla comparado con un *TDA* más simple como la lista.
&nbsp;
## 4. Aclaraciones sobre la implementación y el *TDA* auxiliario
Por conflictos con las firmas de las primitivas de `lista.h`, se necesitó utilizar casteos explícitos para los valores calificados como constantes, específicamente los campos `clave` y `valor` de la estructura de par. Estos valores son casteados en cada instancia que se utilizan como parámetro en primitivas de Lista, cuando se necesita liberar la memoria que ocupan, y en varias otras ocasiones.

En ningún momento realmente se modifican para el usuario (a menos que este lo pida) y simplemente es una cuestión de manipulación interna. En la práctica estos valores son y se aseguran constantes a lo largo del uso, por lo que se mantiene la integridad del contrato.

Además, fue necesario hacer un pequeño cambio a `lista.c` para garantizar el funcionamiento de la función `diccionario_eliminar()`. La primitiva `lista_eliminar()` no contemplaba el caso de que `lista->fin` sea `NULL` antes de acceder a sus datos. Se agregó un condicional para tenerlo en cuenta y evitar errores de acceso inválido en la memoria.



