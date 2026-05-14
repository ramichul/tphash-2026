#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#define FORMATO_LECTURA "%[^,],%[^,],%i,%i,%i%*[^\n]\n"
#define FORMATO_ESCRITURA "%s,%s,%i,%i,%i\n"
#define IDENTIFICADOR_ARCHIVO ".csv"
#define CHAR_DIVISOR_CAMPOS ','
#define INDICADOR_NUEVA_LINEA '\n'

#define MAX_TIPOS 8
#define MAX_NOM_TIPO 5

#define CANT_DESEADA_LECTURA 5
#define TAM_INICIAL_BUFFER 1
#define AJUSTE_TAM_BUFFER 2
#define CANT_COMANDOS_VALIDOS 2
#define CANT_INSTRUCCIONES_VALIDAS 2
#define CANT_MINIMA_ARGUMENTOS 3
#define CANT_ESPERADA_ARG 4
#define CANT_ESPERADA_LONGITUD 4

#define SIN_ERRORES 0
#define ERR_MEMORIA 1
#define LINEA_VACIA 2
#define LINEA_INVALIDA 3
#define ERR_ARCHIVO 4
#define ERR_COMANDO 5
#define ERR_CONTROL 6
#define ERR_BUSCAR 7
#define ERR_LECTURA 8
#define ERR_MOSTRAR 9
#define ERR_CANT_ARGUMENTOS 10

#define ARCHIVO_PRUEBA_INEXISTENTE "ejemplos/asdkasjhfskladjhfksdfhksdf.csv"
#define ARCHIVO_PRUEBA_VACIO "ejemplos/vacio.csv"
#define ARCHIVO_PRUEBA_INVALIDO_1 "ejemplos/invalido_1.csv"
#define ARCHIVO_PRUEBA_INVALIDO_2 "ejemplos/invalido_2.csv"
#define ARCHIVO_PRUEBA_INVALIDO_3 "ejemplos/invalido_3.csv"
#define ARCHIVO_PRUEBA_PARSEO "ejemplos/parseo.csv"
#define ARCHIVO_PRUEBA_MIXTO "ejemplos/mixto.csv"
#define ARCHIVO_PRUEBA_NORMAL "ejemplos/normal.csv"
#define ARCHIVO_PRUEBA_REPETIDOS_1 "ejemplos/repetidos_1.csv"
#define ARCHIVO_PRUEBA_REPETIDOS_2 "ejemplos/repetidos_2.csv"
#define ARCHIVO_PRUEBA_REPETIDOS_3 "ejemplos/repetidos_mayusculas.csv"

#define NOMBRE_SALIDA_PRUEBA "resultado.csv"

#define CANTIDAD_CORRECTA_NORMAL 6
#define CANTIDAD_CORRECTA_REPETIDOS_1 2
#define CANTIDAD_CORRECTA_REPETIDOS_2 1
#define CANTIDAD_CORRECTA_REPETIDOS_3 6
#define NOMBRE_POKEMON_PRESENTE "Pikachu"
#define NOMBRE_POKEMON_NO_PRESENTE "Rayquaza"
#define NOMBRE_PRIMER_POKEMON_ALFABETICO "Bulbasaur"
#define NOMBRE_ULTIMO_POKEMON_ALFABETICO "Squirtle"

#define MSJ_BIENVENIDA \
	"\033[38;5;222;1m                                           __ \n _____ _____ _____ _____ ____  _____ __ __|  |\n|  _  |     |  |  |   __|    \\|   __|  |  |  |\n|   __|  |  |    -|   __|  |  |   __|-   -|__|\n|__|  |_____|__|__|_____|____/|_____|__|__|__|\n\n\n🔴⚪ ¡Bienvenido al sistema de manejo de Pokédex! ⚪🔴\n\n\033[0m"
#define MSJ_DATOS \
	"\033[38;5;223;1mDATOS DEL POKÉMON: \n\033[0m\033[38;5;223mNOMBRE:\033[0m %s\n\033[38;5;223mTIPO:\033[0m %s\n\033[38;5;223mATAQUE:\033[0m %i\n\033[38;5;223mDEFENSA:\033[0m %i\n\033[38;5;223mVELOCIDAD:\033[0m %i\n\n"
#define MSJ_INSTRUCCIONES \
	"El modo de uso es \033[38;5;223m./tp1 [archivo] [comando a ejecutar]\033[0m.\n\nVuelva a correr el programa por terminal utilizando uno de los siguientes comandos como argumento(s):\n\n- \033[38;5;223m./tp1 [archivo] buscar [nombre a buscar]\033[0m: Busca un Pokémon con el nombre especificado e imprime su información por pantalla.\n\n- \033[38;5;223m./tp1 [archivo] mostrar [nombre/tipo]\033[0m: Muestra todos los Pokémon por orden alfabético u ordenados por tipo.\n\n"
#define MSJ_ERR_LECTURA \
	"\033[38;5;202;1mERROR\033[0m: Ocurrió un error al leer el archivo. Por favor, vuelva a intentar.\n"
#define MSJ_ERR_GUARDAR \
	"\033[38;5;202;1mERROR\033[0m: Ocurrió un error al guardar el archivo. Por favor, vuelva a intentar.\n"
#define MSJ_ERR_COMANDO \
	"\033[38;5;202;1mERROR\033[0m: Nombre inválido de comando: \033[38;5;223m%s\033[0m. "
#define MSJ_ERR_INSTRUCCION \
	"\033[38;5;202;1mERROR\033[0m: Nombre inválido de instrucción: ./tp1 %s \033[38;5;223m%s\033[0m. Por favor, consulte las instrucciones ejecutando el programa sin argumentos y vuelva a intentar.\n\n"
#define MSJ_ERR_ARGUMENTOS \
	"\033[38;5;202;1mERROR\033[0m: Cantidad inválida de argumentos para el comando \033[38;5;223m%s\033[0m. Por favor, consulte las instrucciones ejecutando el programa sin argumentos y vuelva a intentar.\n\n"
#define MSJ_POKEMON_NO_ENCONTRADO \
	"\033[38;5;202;1mERROR\033[0m: El Pokémon buscado no se encuentra en su Pokédex actualmente.\n\n"
#define MSJ_EXITO \
	"\033[38;5;222;1m🔴⚪ Comando realizado con éxito. ¡Hasta luego! ⚪🔴\n\n\033[0m"
#define MSJ_VACIA "Su Pokédex está vacía.\n\n"

#endif // CONSTANTES_H_